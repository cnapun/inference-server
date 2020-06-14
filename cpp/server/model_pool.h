#pragma once

#include <google/protobuf/util/json_util.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "cpp/server/models/model.h"
#include "proto/inference.pb.h"
#include "proto/model_spec.pb.h"

namespace models {
class ModelPool {
 public:
  ModelPool() : models_(new std::unordered_map<std::string, std::unique_ptr<Model>>()){};
  ModelPool(const ModelPool &) = delete;
  void operator=(const ModelPool &) = delete;

  void LoadModels(const std::string &global_config_path);

  bool HandleRequest(const inference::InferRequest &request,
                     inference::InferResponse *response) const;

 private:
  void LoadModel(const configs::ModelSpec &spec);

  std::unique_ptr<std::unordered_map<std::string, std::unique_ptr<Model>>> models_;
};
}  // namespace models