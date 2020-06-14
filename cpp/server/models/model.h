#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "cpp/server/transforms/transform.h"
#include "proto/inference.pb.h"
#include "proto/model_spec.pb.h"

namespace models {
class Model {
 public:
  virtual ~Model() = default;

  virtual void LoadSpec(const configs::ModelSpec &spec);

  void InferBatch(const google::protobuf::RepeatedPtrField<inference::InferRequestItem> &items,
                  inference::InferResponse *response) const;

  [[nodiscard]] uint32_t total_dim() const { return total_dim_; }

 protected:
  [[nodiscard]] virtual std::vector<float> InferMatrixInternal(const std::vector<float> &data,
                                                               size_t D, size_t N) const = 0;

  std::unique_ptr<std::mutex> inference_mutex_;

 private:
  [[nodiscard]] std::vector<float> PreprocessItem(const inference::InferRequestItem &item) const;

  std::unique_ptr<std::vector<std::unique_ptr<transforms::Transform>>> transforms_;
  std::unique_ptr<std::vector<std::string>> feature_order_;
  uint32_t total_dim_;
};
}  // namespace models