load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//cpp/server:__subpackages__"])

cc_library(
    name = "model_pool",
    srcs = ["model_pool.cc"],
    hdrs = ["model_pool.h"],
    deps = [
        "//cpp/server/models:model",
        "//cpp/server/models:model_registry",
        "//proto:inference_cc_proto",
        "//proto:model_spec_cc_proto",
    ],
)

cc_binary(
    name = "inference_server",
    srcs = ["inference_server.cc"],
    data = [
        "//data:sample_config",
        "//data:sample_model",
    ],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":model_pool",
        "//proto:inference_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_gflags//:gflags",
    ],
)
