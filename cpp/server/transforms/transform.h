#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "proto/inference.pb.h"
#include "proto/model_spec.pb.h"

namespace transforms {
class Transform {
 public:
  virtual void LoadTransform(const configs::FeatureSpec &spec) {
    spec_ = std::make_unique<configs::FeatureSpec>(spec);
  };
  //  explicit Transform(const configs::FeatureSpec &spec)
  //      : spec_() {}

  [[nodiscard]] virtual std::vector<float> Apply(
      const std::optional<inference::Feature> &feature) const = 0;

  virtual ~Transform() = default;

  [[nodiscard]] uint32_t dimension() const { return spec_->dimensions(); }
  [[nodiscard]] std::string name() const { return spec_->name(); }

 protected:
  std::unique_ptr<const configs::FeatureSpec> spec_;
};
}  // namespace transforms