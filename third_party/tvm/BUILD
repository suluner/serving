# TVM (tvm.ai) library.
# from https://github.com/dmlc/tvm.git

package(
    default_visibility = ["//visibility:public"],
)

licenses(["notice"])  # Apache

exports_files(["LICENSE"])

cc_library(
    name = "tvm_runtime",
    srcs = glob([
      "src/runtime/*.cc",
      "src/runtime/vm/*.cc"
    ]),
    hdrs = glob([
      "3rdparty/dmlc-core/include/**/*.h",
      "include/**/*.h",
      "include/tvm/runtime/**/*.h",
      "3rdparty/dlpack/include/**/*.h",
      "src/runtime/**/*.h",
      "src/runtime/*.h",
    ]),
    includes = [
      "3rdparty/dmlc-core/include",
	    "include",
	    "3rdparty/dlpack/include",
		  "src/runtime",
    ],
    alwayslink = 1,
)