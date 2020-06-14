#include "xgb_model.h"

#include <xgboost/c_api.h>
#include <xgboost/predictor.h>

namespace models {
void XgbModel::LoadSpec(const configs::ModelSpec &spec) {
  Model::LoadSpec(spec);
  xgboost_model_.reset(xgboost::Learner::Create({}));
  std::unique_ptr<dmlc::Stream> inp(dmlc::Stream::Create(spec.model_path().c_str(), "r"));
  xgboost_model_->LoadModel(inp.get());
}

std::vector<float> XgbModel::InferMatrixInternal(const std::vector<float> &data, size_t D,
                                                 size_t N) const {
  DMatrixHandle dmat_handle;
  int success = XGDMatrixCreateFromMat(data.data(), N, D, 0, &dmat_handle);
  if (success != 0) {
    throw std::runtime_error("failed to create dmatrix");
  }
  std::shared_ptr<xgboost::DMatrix> dmat =
      *static_cast<std::shared_ptr<xgboost::DMatrix> *>(dmat_handle);
  xgboost::HostDeviceVector<xgboost::bst_float> preds_xgb;
  {
    std::lock_guard<std::mutex> lock(*inference_mutex_);
    xgboost_model_->Predict(dmat, false, &preds_xgb);
  }
  return preds_xgb.HostVector();
}

}  // namespace models