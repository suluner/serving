# TVM (tvm.ai) library.
# from https://github.com/dmlc/tvm.git
load(
    "@local_config_cuda//cuda:build_defs.bzl",
    "if_cuda",
)

package(
    default_visibility = ["//visibility:public"],
)

licenses(["notice"])  # Apache

exports_files(["LICENSE"])

cc_library(
    name = "cuda_support",
    srcs = [
      "src/runtime/cuda/cuda_module.cc",
      "src/runtime/cuda/cuda_device_api.cc",
    ],
    hdrs = glob([
      "3rdparty/dmlc-core/include/**/*.h",
      "3rdparty/compiler-rt/*.h",
      "3rdparty/dlpack/include/**/*.h",
      "include/tvm/runtime/**/*.h",
      "include/tvm/runtime/*.h",
      "src/runtime/**/*.h",
      "src/runtime/*.h",
      "src/support/*.h",
    ]),
    includes = [
      "3rdparty/dmlc-core/include",
      "3rdparty/compiler-rt",
      "3rdparty/dlpack/include",
	    "include",
	    "src/runtime",
      "src/support",
    ],
    deps = [
      "@my_cuda//:cuda-lib"
    ],
    alwayslink = 1,
)

cc_library(
    name = "tvm_runtime",
    srcs = glob([
      "src/runtime/*.cc",
      "src/runtime/vm/*.cc",
      "src/runtime/graph_executor/*.cc"
    ]),
    hdrs = glob([
      "3rdparty/dmlc-core/include/**/*.h",
      "3rdparty/compiler-rt/*.h",
      "3rdparty/dlpack/include/**/*.h",
      "include/tvm/runtime/**/*.h",
      "include/tvm/runtime/*.h",
      "src/runtime/**/*.h",
      "src/runtime/*.h",
      "src/support/*.h",
    ]),
    includes = [
      "3rdparty/dmlc-core/include",
      "3rdparty/compiler-rt",
      "3rdparty/dlpack/include",
	    "include",
	    "src/runtime",
      "src/support",
    ],
    deps = if_cuda([
      ":cuda_support",
    ]),
    defines = if_cuda([
      "CUDA",
    ]),
    alwayslink = 1,
)
