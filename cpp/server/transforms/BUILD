load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//cpp/server/transforms:__subpackages__"])

cc_library(
    name = "transform",
    hdrs = ["transform.h"],
    copts = ["-Wall"],
    visibility = ["//cpp/server:__subpackages__"],
    deps = [
        "//proto:inference_cc_proto",
    ],
)

cc_library(
    name = "categorical_transforms",
    srcs = ["categorical_transforms.cc"],
    hdrs = ["categorical_transforms.h"],
    copts = ["-Wall"],
    deps = [
        ":transform",
        "//proto:inference_cc_proto",
        "//proto:model_spec_cc_proto",
    ],
)

cc_library(
    name = "continuous_transforms",
    hdrs = ["continuous_transforms.h"],
    copts = ["-Wall"],
    deps = [
        ":transform",
        "//proto:inference_cc_proto",
        "//proto:model_spec_cc_proto",
    ],
)

cc_library(
    name = "transform_registry",
    srcs = ["transform_registry.cc"],
    hdrs = ["transform_registry.h"],
    copts = ["-Wall"],
    visibility = ["//cpp/server:__subpackages__"],
    deps = [
        ":categorical_transforms",
        ":continuous_transforms",
        ":transform",
        "//proto:model_spec_cc_proto",
    ],
)
