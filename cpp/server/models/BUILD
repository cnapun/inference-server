load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//cpp/server/models:__subpackages__"])

cc_library(
    name = "model",
    srcs = ["model.cc"],
    hdrs = ["model.h"],
    copts = ["-Wall"],
    visibility = ["//cpp/server:__subpackages__"],
    deps = [
        "//cpp/server/transforms:transform",
        "//cpp/server/transforms:transform_registry",
        "//proto:inference_cc_proto",
        "//proto:model_spec_cc_proto",
    ],
)

cc_library(
    name = "xgb_model",
    srcs = ["xgb_model.cc"],
    hdrs = ["xgb_model.h"],
    copts = ["-Wall"],
    deps = [
        ":model",
        "//:xgboost",
        "//proto:inference_cc_proto",
        "//proto:model_spec_cc_proto",
    ],
)

cc_library(
    name = "model_registry",
    srcs = ["model_registry.cc"],
    hdrs = ["model_registry.h"],
    copts = ["-Wall"],
    visibility = ["//cpp/server:__subpackages__"],
    deps = [
        ":model",
        ":xgb_model",
        "//proto:model_spec_cc_proto",
    ],
)
