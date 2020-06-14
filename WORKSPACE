load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)

load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")

rules_proto_dependencies()

rules_proto_toolchains()

##### gRPC Rules for Bazel
##### See https://github.com/grpc/grpc/blob/master/src/cpp/README.md#make
http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "bda7b52bab00592c115d5c2757ca729b665ed39cdf048541bf8aab212464c5a0",
    strip_prefix = "grpc-7d89dbb311f049b43bda7bbf6f7d7bf1b4c24419",
    urls = [
        "https://github.com/grpc/grpc/archive/7d89dbb311f049b43bda7bbf6f7d7bf1b4c24419.tar.gz",
    ],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

# Not mentioned in official docs... mentioned here https://github.com/grpc/grpc/issues/20511
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

http_archive(
    name = "com_google_gflags",
    sha256 = "b20f58e7f210ceb0e768eb1476073d0748af9b19dfbbf53f4fd16e3fb49c5ac8",
    strip_prefix = "gflags-e171aa2d15ed9eb17054558e0b3a6a413bb01067",
    urls = ["https://github.com/gflags/gflags/archive/e171aa2d15ed9eb17054558e0b3a6a413bb01067.tar.gz"],
)

http_archive(
    name = "com_google_benchmark",
    sha256 = "8dcd0c9c17265584343e209dce938d8834cd8356ea5bda98045ee7ff35793d30",
    strip_prefix = "benchmark-8039b4030795b1c9b8cedb78e3a2a6fb89574b6e",
    urls = ["https://github.com/google/benchmark/archive/8039b4030795b1c9b8cedb78e3a2a6fb89574b6e.tar.gz"],
)
