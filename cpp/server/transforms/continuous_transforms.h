#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "cpp/server/transforms/transform.h"
#include "proto/inference.pb.h"
#include "proto/model_spec.pb.h"

namespace transforms {
class ContinuousFloatTransform : public Transform {
 public:
  [[nodiscard]] std::vector<float> Apply(
      const std::optional<inference::Feature> &feature) const override {
    if (feature) {
      return {feature.value().f32_value()};
    } else {
      return {spec_->f32_cont().default_value()};
    }
  }
};
}  // namespace transforms