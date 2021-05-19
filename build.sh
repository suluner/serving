!# /bin/bash

TF_SERVING_BUILD_OPTIONS="--config=release"

TF_SERVING_BAZEL_OPTIONS=""

bazel build --color=yes --curses=yes \
    ${TF_SERVING_BAZEL_OPTIONS} \
    --verbose_failures \
    --output_filter=DONT_MATCH_ANYTHING \
    ${TF_SERVING_BUILD_OPTIONS} \
    tensorflow_serving/model_servers:tensorflow_model_server
