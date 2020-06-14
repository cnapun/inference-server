#pragma once

#include "cpp/server/transforms/transform.h"
#include "proto/model_spec.pb.h"

namespace transforms {
Transform* LoadTransform(const configs::FeatureSpec& feature_spec);
}