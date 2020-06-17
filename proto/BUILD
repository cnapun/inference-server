load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

package(default_visibility = ["//visibility:public"])

proto_library(
    name = "inference_proto",
    srcs = ["inference.proto"],
)

proto_library(
    name = "model_spec_proto",
    srcs = ["model_spec.proto"],
)

proto_library(
    name = "linear_model_proto",
    srcs = ["linear_model.proto"],
)

cc_proto_library(
    name = "inference_cc_proto",
    deps = [":inference_proto"],
)

cc_grpc_library(
    name = "inference_cc_grpc",
    srcs = [":inference_proto"],
    grpc_only = True,
    deps = [":inference_cc_proto"],
)

cc_proto_library(
    name = "model_spec_cc_proto",
    deps = [":model_spec_proto"],
)

cc_proto_library(
    name = "linear_model_cc_proto",
    deps = [":linear_model_proto"],
)
