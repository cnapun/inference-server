#include "model_pool.h"

#include <fstream>
#include <iostream>
#include <streambuf>

#include "cpp/server/models/model_registry.h"
namespace models {
void models::ModelPool::LoadModels(const std::string &global_config_path) {
  std::ifstream inp(global_config_path);
  GOOGLE_CHECK(inp.is_open()) << "inp should be open";
  std::string str((std::istreambuf_iterator<char>(inp)), std::istreambuf_iterator<char>());
  configs::GlobalModelConfig config;
  google::protobuf::util::Status status = google::protobuf::util::JsonStringToMessage(str, &config);
  if (status != google::protobuf::util::Status::OK) {
    throw std::runtime_error("status=" + status.ToString());
  }
  for (const auto &model : config.models()) {
    this->LoadModel(model);
  }
}

bool ModelPool::HandleRequest(const inference::InferRequest &request,
                              inference::InferResponse *response) const {
  const auto &it = models_->find(request.model());
  if (it == models_->end()) {
    return false;
  }
  try {
    (*it).second->InferBatch(request.requests(), response);
    return true;
  } catch (std::exception &exception) {
    std::cout << "encountered exception: " << exception.what() << std::endl;
    return false;
  }
}

void ModelPool::LoadModel(const configs::ModelSpec &spec) {
  if (models_->find(spec.name()) != models_->end()) {
    throw std::runtime_error("duplicate model definition found for model name " + spec.name());
  }

  (*models_)[spec.name()] = std::unique_ptr<Model>(models::LoadModel(spec));
}
}  // namespace models