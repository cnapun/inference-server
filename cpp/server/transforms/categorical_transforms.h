#pragma once

#include <memory>
#include <optional>

#include "proto/inference.pb.h"
#include "proto/model_spec.pb.h"
#include "transform.h"

namespace transforms {
class CategoricalStringTransform : public Transform {
 public:
  [[nodiscard]] std::vector<float> Apply(
      const std::optional<inference::Feature> &feature) const override;

  void LoadTransform(const configs::FeatureSpec &spec) override;
};

class CategoricalI32Transform : public Transform {
 public:
  [[nodiscard]] std::vector<float> Apply(
      const std::optional<inference::Feature> &feature) const override;
};
}  // namespace transforms