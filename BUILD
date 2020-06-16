load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

toolchain(
    name = "preinstalled_cmake",
    toolchain = "@rules_foreign_cc//tools/build_defs/native_tools:preinstalled_cmake",
    toolchain_type = "@rules_foreign_cc//tools/build_defs:cmake_toolchain",
)

toolchain(
    name = "preinstalled_ninja",
    toolchain = "@rules_foreign_cc//tools/build_defs/native_tools:preinstalled_ninja",
    toolchain_type = "@rules_foreign_cc//tools/build_defs:ninja_toolchain",
)

cmake_external(
    name = "xgboost",
    cmake_options = {
        #        "JOBS": 8,
        "CMAKE_CXX_FLAGS": "-Wall",
        "CMAKE_BUILD_PARALLEL_LEVEL": "8",
    },
    lib_source = "@xgboost//:all",
    shared_libraries = select({
        "@bazel_tools//src/conditions:darwin": ["libxgboost.dylib"],
        "//conditions:default": ["libxgboost.so"],
    }),
    visibility = ["//visibility:public"],
)
