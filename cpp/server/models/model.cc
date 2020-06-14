#include "cpp/server/models/model.h"

#include <optional>

#include "cpp/server/transforms/transform.h"
#include "cpp/server/transforms/transform_registry.h"

using google::protobuf::RepeatedPtrField;
using transforms::Transform;

namespace {
void ValidateModelSpec(const configs::ModelSpec &spec) {
  GOOGLE_CHECK(spec.feature_order_size() == spec.transforms_size());
  GOOGLE_CHECK(spec.feature_order_size() != 0);
}
}  // namespace

namespace models {
void Model::LoadSpec(const configs::ModelSpec &spec) {
  ValidateModelSpec(spec);
  transforms_ = std::make_unique<std::vector<std::unique_ptr<transforms::Transform>>>();
  feature_order_ = std::make_unique<std::vector<std::string>>();
  inference_mutex_ = std::make_unique<std::mutex>();
  feature_order_->reserve(spec.feature_order_size());
  std::unordered_map<std::string, configs::FeatureSpec> name_to_spec;
  for (const auto &transform : spec.transforms()) {
    name_to_spec[transform.name()] = transform;
  }
  transforms_->reserve(spec.feature_order_size());
  for (const auto &feat_name : spec.feature_order()) {
    feature_order_->push_back(feat_name);
    transforms_->push_back(
        std::unique_ptr<Transform>(transforms::LoadTransform(name_to_spec.at(feat_name))));
  }
  total_dim_ = 0;
  for (const auto &transform : *transforms_) {
    total_dim_ += transform->dimension();
  }
}

std::vector<float> Model::PreprocessItem(const inference::InferRequestItem &item) const {
  std::vector<float> out;
  out.reserve(total_dim());
  for (int i = 0; i < feature_order_->size(); ++i) {
    const auto &feat_it = item.features().find((*feature_order_)[i]);
    std::optional<inference::Feature> feat = std::nullopt;
    if (feat_it != item.features().end()) {
      feat = feat_it->second;
    }
    const std::vector<float> &converted_feat = transforms_->at(i)->Apply(feat);
    out.insert(out.end(), converted_feat.begin(), converted_feat.end());
  }
  return out;
}

void Model::InferBatch(const google::protobuf::RepeatedPtrField<inference::InferRequestItem> &items,
                       inference::InferResponse *response) const {
  std::vector<std::string> ids;
  ids.reserve(items.size());
  std::vector<float> feats;

  static size_t D = total_dim();
  static size_t N = items.size();
  feats.reserve(D * N);

  for (const auto &item : items) {
    ids.push_back(item.id());
    const std::vector<float> &feat = PreprocessItem(item);
    feats.insert(feats.end(), feat.begin(), feat.end());
  }
  const std::vector<float> &pred_vector = InferMatrixInternal(feats, D, N);
  if (pred_vector.size() != N) {
    throw std::runtime_error("expected preds.size() == N");
  }
  for (int i = 0; i < N; ++i) {
    inference::Feature pred;
    pred.set_f32_value(pred_vector[i]);
    (*(response->mutable_results()))[ids[i]] = std::move(pred);
  }
}
}  // namespace models