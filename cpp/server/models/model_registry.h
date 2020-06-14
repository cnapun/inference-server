#pragma once

#include "cpp/server/models/model.h"
#include "proto/model_spec.pb.h"

namespace models {
Model* LoadModel(const configs::ModelSpec& spec);
}