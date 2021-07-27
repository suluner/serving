/* Copyright 2018 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_SERVING_MODEL_SERVERS_PREDICTION_SERVICE_IMPL_H_
#define TENSORFLOW_SERVING_MODEL_SERVERS_PREDICTION_SERVICE_IMPL_H_

#include "tensorflow_serving/apis/prediction_service.grpc.pb.h"
#include "tensorflow_serving/model_servers/server_core.h"
#include "tensorflow_serving/model_servers/predictor.h"
#include "tensorflow_serving/servables/tensorflow/predict_impl.h"
#include "tensorflow_serving/servables/tvm/predict_impl.h"
#include "tensorflow_serving/servables/tensorflow/thread_pool_factory.h"
#include "tensorflow_serving/model_servers/model_platform_types.h"
#include "tensorflow_serving/model_servers/get_model_metadata.h"
#include "tensorflow_serving/servables/tensorflow/get_model_metadata_impl.h"
#include "tensorflow_serving/servables/tvm/get_model_metadata_impl.h"

namespace tensorflow {
namespace serving {

class PredictionServiceImpl final : public PredictionService::Service {
 public:
  // Options for configuring a PredictionServiceImpl object.
  struct Options {
    ServerCore* server_core;
    bool enforce_session_run_timeout;
    ThreadPoolFactory* thread_pool_factory = nullptr;
  };

  explicit PredictionServiceImpl(const Options& options)
      : core_(options.server_core),
        enforce_session_run_timeout_(options.enforce_session_run_timeout),
        thread_pool_factory_(options.thread_pool_factory) {
    if(!core_->GetModelPlatform().compare(kTVMModelPlatform)) {
      predictor_ = std::make_unique<TVMPredictor>();
      get_model_meta_data_ = std::make_unique<TVMGetModelMetadata>();
    } else {
      predictor_ = std::make_unique<TensorflowPredictor>();
      get_model_meta_data_ = std::make_unique<TensorflowGetModelMetadata>();
    }
  }

  ::grpc::Status Predict(::grpc::ServerContext* context,
                         const PredictRequest* request,
                         PredictResponse* response) override;

  ::grpc::Status GetModelMetadata(::grpc::ServerContext* context,
                                  const GetModelMetadataRequest* request,
                                  GetModelMetadataResponse* response) override;

  ::grpc::Status Classify(::grpc::ServerContext* context,
                          const ClassificationRequest* request,
                          ClassificationResponse* response) override;

  ::grpc::Status Regress(::grpc::ServerContext* context,
                         const RegressionRequest* request,
                         RegressionResponse* response) override;

  ::grpc::Status MultiInference(::grpc::ServerContext* context,
                                const MultiInferenceRequest* request,
                                MultiInferenceResponse* response) override;

 private:
  ServerCore* core_;
  std::unique_ptr<Predictor> predictor_;
  const bool enforce_session_run_timeout_;
  ThreadPoolFactory* thread_pool_factory_;
  std::unique_ptr<BaseGetModelMetadata> get_model_meta_data_;
};

}  // namespace serving
}  // namespace tensorflow

#endif  // TENSORFLOW_SERVING_MODEL_SERVERS_PREDICTION_SERVICE_IMPL_H_
