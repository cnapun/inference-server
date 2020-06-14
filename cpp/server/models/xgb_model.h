#pragma once

#include <xgboost/learner.h>

#include "cpp/server/models/model.h"

namespace models {
class XgbModel : public Model {
 public:
  XgbModel() = default;

  void LoadSpec(const configs::ModelSpec &spec) override;

 protected:
  [[nodiscard]] std::vector<float> InferMatrixInternal(const std::vector<float> &data, size_t D,
                                                       size_t N) const override;

 private:
  std::unique_ptr<xgboost::Learner> xgboost_model_;
};
}  // namespace models