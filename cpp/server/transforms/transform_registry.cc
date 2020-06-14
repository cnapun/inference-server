#include "transform_registry.h"

#include "cpp/server/transforms/categorical_transforms.h"
#include "cpp/server/transforms/continuous_transforms.h"

namespace transforms {
Transform* LoadTransform(const configs::FeatureSpec& feature_spec) {
  GOOGLE_CHECK(feature_spec.dimensions() > 0);
  GOOGLE_CHECK(!feature_spec.name().empty());
  Transform* transform = nullptr;
  switch (feature_spec.transform_spec_case()) {
    case configs::FeatureSpec::kStrCat:
      transform = new CategoricalStringTransform();
      break;
    case configs::FeatureSpec::kI32Cat:
      transform = new CategoricalI32Transform();
      break;
    case configs::FeatureSpec::kF32Cont:
      transform = new ContinuousFloatTransform();
      break;
    case configs::FeatureSpec::TRANSFORM_SPEC_NOT_SET:
      throw std::invalid_argument("transform_spec not set");
  }
  transform->LoadTransform(feature_spec);
  return transform;
}
}  // namespace transforms