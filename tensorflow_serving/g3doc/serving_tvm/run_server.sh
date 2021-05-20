#! /bin/bash

./tensorflow_model_server --port=6003 --rest_api_port=6004 --model_config_file=/root/serving/tensorflow_serving/g3doc/serving_tvm/model_config.txt
