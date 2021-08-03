package(
    default_visibility = ["//visibility:public"],
)

licenses(["notice"])  # Apache

exports_files(["LICENSE"])

cc_library(
    name = "cuda-lib",
    srcs = glob([
      "lib64/*.so",
      "lib64/**/*.so"
    ]),
    hdrs = glob([
      "include/*.h",
      "include/**/*.h"
    ]),
    includes = [
      "include"
    ],
    alwayslink = 1,
)