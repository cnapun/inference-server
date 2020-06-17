#include "model_pool.h"

#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <streambuf>

#include "cpp/server/models/model_registry.h"

namespace models {
void models::ModelPool::LoadModels(const std::string &global_config_path) {
  std::ifstream inp(global_config_path);
  CHECK(inp.is_open()) << "inp should be open";
  std::string str((std::istreambuf_iterator<char>(inp)), std::istreambuf_iterator<char>());
  configs::GlobalModelConfig config;
  google::protobuf::util::Status status = google::protobuf::util::JsonStringToMessage(str, &config);
  CHECK(status.ok()) << status.error_message();

  for (const auto &model : config.models()) {
    LOG(INFO) << "loading model from spec: " << model.DebugString();
    this->LoadModel(model);
  }
}

bool ModelPool::HandleRequest(const inference::InferRequest &request,
                              inference::InferResponse *response) const {
  const auto &it = models_->find(request.model());
  if (it == models_->end()) {
    LOG(ERROR) << "model " << request.model() << " not found";
    return false;
  }
  try {
    (*it).second->InferBatch(request.requests(), response);
    return true;
  } catch (std::exception &exception) {
    LOG(ERROR) << "encountered exception: " << exception.what();
    return false;
  }
}

void ModelPool::LoadModel(const configs::ModelSpec &spec) {
  CHECK(models_->find(spec.name()) == models_->end())
      << "duplicate model definition found for model name " + spec.name();

  (*models_)[spec.name()] = std::unique_ptr<Model>(models::LoadModel(spec));
}
}  // namespace models