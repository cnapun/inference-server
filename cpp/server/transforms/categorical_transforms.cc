#include "cpp/server/transforms/categorical_transforms.h"

namespace transforms {
std::vector<float> CategoricalStringTransform::Apply(
    const std::optional<inference::Feature> &feature) const {
  std::vector<float> out(spec_->dimensions(), 0.0);
  const auto &encoding_map = spec_->str_cat().encoding();
  const uint32_t default_ix = spec_->str_cat().default_value();
  if (!feature || feature->str_value().empty()) {
    out[default_ix] = 1.0;
  } else {
    const auto &res = encoding_map.find(feature->str_value());
    if (res == encoding_map.end()) {
      out[default_ix] = 1.0;
    } else {
      out[res->second] = 1.0;
    }
  }
  return out;
}

void CategoricalStringTransform::LoadTransform(const configs::FeatureSpec &spec) {
  Transform::LoadTransform(spec);
  if (spec_->str_cat().default_value() >= spec_->dimensions()) {
    throw std::runtime_error("default_value must be less than dimensions");
  }
  for (const auto &pair : spec_->str_cat().encoding()) {
    if (pair.second >= spec_->dimensions()) {
      throw std::runtime_error("encoding index must be less than dimensions");
    }
  }
}

std::vector<float> CategoricalI32Transform::Apply(
    const std::optional<inference::Feature> &feature) const {
  std::vector<float> out(spec_->dimensions(), 0.0);
  const auto &encoding_map = spec_->i32_cat().encoding();
  const uint32_t default_ix = spec_->i32_cat().default_value();
  if (!feature) {
    out[default_ix] = 1.0;
  } else {
    const auto &res = encoding_map.find(feature->i32_value());
    if (res == encoding_map.end()) {
      out[default_ix] = 1.0;
    } else {
      out[res->second] = 1.0;
    }
  }
  return out;
}
}  // namespace transforms