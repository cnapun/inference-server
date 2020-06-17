#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>

#include <iostream>
#include <string>

#include "proto/inference.grpc.pb.h"
#include "proto/inference.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using inference::Feature;
using inference::InferRequest;
using inference::InferRequestItem;
using inference::InferResponse;
using inference::ModelInference;

DEFINE_int32(port, 50051, "Port to connect to");
DEFINE_string(host, "localhost", "Host to ping");

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::shared_ptr<Channel> channel(grpc::CreateChannel(FLAGS_host + ":" + std::to_string(FLAGS_port),
                                                       grpc::InsecureChannelCredentials()));
  const auto &stub = ModelInference::NewStub(channel);
  InferRequest request;
  request.set_model("exp1_net");
  InferRequestItem i1;
  i1.set_id("i1");
  Feature f;
  f.set_name("gender");
  f.set_str_value("f");
  (*i1.mutable_features())["gender"] = f;
  InferRequestItem i2;
  i2.set_id("i2");
  (*i2.mutable_features())["gender"] = f;
  Feature f2;
  f2.set_name("age");
  f2.set_f32_value(12);
  (*i2.mutable_features())["age"] = f2;

  request.mutable_requests()->Add(std::move(i1));
  request.mutable_requests()->Add(std::move(i2));
  ClientContext context;
  InferResponse response;
  Status status = stub->InferBatch(&context, request, &response);
  if (status.ok()) {
    std::string s;
    google::protobuf::util::MessageToJsonString(response, &s);
    std::cout << "Status: OK. response:" << std::endl << s << std::endl;
  } else {
    std::cout << status.error_code() << ": " << status.error_message() << std::endl;
  }
  return 0;
}