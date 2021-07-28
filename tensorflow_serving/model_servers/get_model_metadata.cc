#include "tensorflow_serving/model_servers/get_model_metadata.h"

namespace tensorflow {
namespace serving {

Status BaseGetModelMetadata::ValidateGetModelMetadataRequest(const GetModelMetadataRequest& request) {
  if (request.metadata_field_size() == 0) {
    return tensorflow::Status(
        tensorflow::error::INVALID_ARGUMENT,
        "GetModelMetadataRequest must specify at least one metadata_field");
  }
  for (const auto& metadata_field : request.metadata_field()) {
    if (metadata_field != BaseGetModelMetadata::kSignatureDef) {
      return tensorflow::errors::InvalidArgument(
          "Metadata field ", metadata_field, " is not supported");
    }
  }
  return tensorflow::Status::OK();
}

Status BaseGetModelMetadata::GetModelMetadata(
    ServerCore* core, const GetModelMetadataRequest& request,
    GetModelMetadataResponse* response) {
  if (!request.has_model_spec()) {
    return tensorflow::Status(tensorflow::error::INVALID_ARGUMENT,
                              "Missing ModelSpec");
  }
  return GetModelMetadataWithModelSpec(core, request.model_spec(), request,
                                       response);
}

}
}