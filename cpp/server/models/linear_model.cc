#include "linear_model.h"

#include <glog/logging.h>
#include <google/protobuf/util/json_util.h>

#include <fstream>
#include <iostream>
#include <memory>

#include "proto/linear_model.pb.h"

void models::LinearModel::LoadSpec(const configs::ModelSpec &spec) {
  Model::LoadSpec(spec);
  std::ifstream inp(spec.model_path());
  CHECK(inp.is_open()) << "inp should be open (opening '" << spec.model_path() << "')";
  std::string str((std::istreambuf_iterator<char>(inp)), std::istreambuf_iterator<char>());
  models::LinearModelDefinition model;
  CHECK(google::protobuf::util::JsonStringToMessage(str, &model).ok());
  weights_ = std::make_unique<std::vector<float>>();
  weights_->insert(weights_->end(), model.weights().begin(), model.weights().end());
  CHECK_EQ(weights_->size(), total_dim());
}

std::vector<float> models::LinearModel::InferMatrixInternal(const std::vector<float> &data,
                                                            size_t D, size_t N) const {
  CHECK_EQ(data.size(), D * N);
  CHECK_EQ(weights_->size(), D);
  std::vector<float> out;
  out.resize(N);
  const float *raw_data = data.data();
  for (int i = 0; i < N; ++i) {
    float dp = 0;
    for (int j = 0; j < D; ++j) {
      dp += raw_data[i * D + j] * (*weights_)[j];
    }
    out[i] = dp;
  }
  return out;
}
