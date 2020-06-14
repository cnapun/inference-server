load("@rules_cc//cc:defs.bzl", "cc_binary")

package(default_visibility = ["//visibility:__pkg__"])

cc_binary(
    name = "inference_client",
    srcs = ["inference_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:inference_cc_grpc",
        "//proto:inference_cc_proto",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_gflags//:gflags",
    ],
)

cc_binary(
    name = "inference_client_bench",
    srcs = ["inference_client_benchmark.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        "//proto:inference_cc_grpc",
        "//proto:inference_cc_proto",
        "@com_github_grpc_grpc//:grpc++",
        "@com_google_benchmark//:benchmark",
    ],
)
