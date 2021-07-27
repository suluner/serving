# Description: Tensorflow Serving tvm servable.

package(
    default_visibility = ["//tensorflow_serving:internal"],
    features = ["-layering_check"],
)

licenses(["notice"])  # Apache 2.0

filegroup(
    name = "all_files",
    srcs = glob(
        ["**/*"],
        exclude = [
            "**/METADATA",
            "**/OWNERS",
            "g3doc/sitemap.md",
        ],
    ),
)

cc_library(
    name = "tvm_source_adapter",
    srcs = ["tvm_source_adapter.cc", "tvm_factory.cc"],
    hdrs = ["tvm_source_adapter.h", "tvm_factory.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":tvm_source_adapter_proto",
        ":tvm_config_proto",
        ":tvm_loader",
        "@org_tensorflow//tensorflow/core:framework",
        "@org_tensorflow//tensorflow/core:lib",
        "//tensorflow_serving/apis:input_proto",
        "//tensorflow_serving/core:simple_loader",
        "//tensorflow_serving/core:source_adapter",
        "//tensorflow_serving/core:storage_path",
    ],
    alwayslink = 1,
)

cc_library(
    name = "tvm_loader",
    srcs = ["tvm_loader.cc"],
    hdrs = ["tvm_loader.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "@com_github_suluner_tvm//:tvm_runtime",
        ":ndarray_util",
        "//tensorflow_serving/core:simple_loader",
    ],
    includes = ["@com_github_suluner_tvm//3rdparty/dmlc-core/include",
	        "@com_github_suluner_tvm//include",
	        "@com_github_suluner_tvm//3rdparty/dlpack/include",
		"@com_github_suluner_tvm//src/runtime"],
    alwayslink = 1,
)

cc_library(
    name = "predict_impl",
    srcs = ["predict_impl.cc"],
    hdrs = ["predict_impl.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        ":ndarray_util",
        "//tensorflow_serving/apis:predict_proto",
        "//tensorflow_serving/core:servable_handle",
        "//tensorflow_serving/model_servers:server_core",
    ],
)

cc_library(
    name = "ndarray_util",
    srcs = ["ndarray_util.cc"],
    hdrs = ["ndarray_util.h", "tvm_loader.h",
    ],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "@com_github_suluner_tvm//:tvm_runtime",
        "//tensorflow_serving/apis:predict_proto",
        "//tensorflow_serving/core:servable_handle",
        "@org_tensorflow//tensorflow/core:framework",
        "@org_tensorflow//tensorflow/core:lib",
        "@com_google_absl//absl/strings",
    ],
    includes = ["@com_github_suluner_tvm//3rdparty/dmlc-core/include",
	        "@com_github_suluner_tvm//include",
	        "@com_github_suluner_tvm//3rdparty/dlpack/include",
		"@com_github_suluner_tvm//src/runtime"],
)

cc_library(
    name = "get_model_metadata_impl",
    srcs = ["get_model_metadata_impl.cc"],
    hdrs = ["get_model_metadata_impl.h"],
    visibility = [
        "//visibility:public",
    ],
    deps = [
        "//tensorflow_serving/apis:get_model_metadata_proto",
        "//tensorflow_serving/core:servable_handle",
        "//tensorflow_serving/model_servers:server_core",
    ],
)

cc_test(
    name = "tvm_source_adapter_test",
    size = "medium",
    srcs = ["tvm_source_adapter_test.cc"],
    deps = [
        ":tvm_source_adapter",
        ":tvm_source_adapter_proto",
        ":tvm_config_proto",
        "//tensorflow_serving/core:loader",
        "//tensorflow_serving/core:servable_data",
        "//tensorflow_serving/core/test_util:test_main",
        "//tensorflow_serving/util:any_ptr",
    ],
)

load("//tensorflow_serving:serving.bzl", "serving_proto_library")

serving_proto_library(
    name = "tvm_source_adapter_proto",
    srcs = ["tvm_source_adapter.proto"],
    deps = [
        ":tvm_config_proto",
    ],
    visibility = [
        "//visibility:public",
    ],
    cc_api_version = 2,
)

serving_proto_library(
    name = "tvm_config_proto",
    srcs = ["tvm_config.proto"],
    visibility = [
        "//visibility:public",
    ],
    cc_api_version = 2,
)