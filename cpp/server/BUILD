load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//cpp/server:__subpackages__"])

cc_library(
    name = "model_pool",
    srcs = ["model_pool.cc"],
    hdrs = ["model_pool.h"],
    copts = ["-Wall"],
    deps = [
        "//cpp/server/models:model",
        "//cpp/server/models:model_registry",
        "//proto:inference_cc_proto",
        "//proto:model_spec_cc_proto",
        "@com_github_google_glog//:glog",
    ],
)

cc_binary(
    name = "server",
    srcs = ["inference_server.cc"],
    copts = ["-Wall"],
    data = [
        "//data:sample_config",
        "//data:sample_models",
    ],
    defines = ["BAZEL_BUILD"],
    visibility = [
        "//cpp/server:__subpackages__",
        "//docker:__subpackages__",
    ],
    deps = [
        ":model_pool",
        "//proto:inference_cc_grpc",
        "@com_github_gflags_gflags//:gflags",
        "@com_github_google_glog//:glog",
        "@com_github_grpc_grpc//:grpc++",
    ],
)
