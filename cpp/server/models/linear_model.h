#pragma once

#include "cpp/server/models/model.h"

namespace models {
class LinearModel : public Model {
 public:
  void LoadSpec(const configs::ModelSpec &spec) override;

 protected:
  [[nodiscard]] std::vector<float> InferMatrixInternal(const std::vector<float> &data, size_t D,
                                                       size_t N) const override;

 private:
  std::unique_ptr<std::vector<float>> weights_;
};
}  // namespace models
