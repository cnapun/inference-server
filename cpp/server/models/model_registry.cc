
#include "model_registry.h"

#include "cpp/server/models/xgb_model.h"

namespace models {
Model *LoadModel(const configs::ModelSpec &spec) {
  Model *model = nullptr;
  switch (spec.model_type()) {
    case configs::XGBOOST:
      model = new XgbModel;
      break;
    default:
      throw std::invalid_argument("model_type must be set");
  }
  model->LoadSpec(spec);
  return model;
}
}  // namespace models