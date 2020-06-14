#include <benchmark/benchmark.h>
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

InferRequest GenRequest() {
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
  return request;
}

class GrpcFixture : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State &state) override {
    request_ = GenRequest();
    stub_ = ModelInference::NewStub(
        grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  }

  InferRequest request_;



  
  std::unique_ptr<ModelInference::Stub> stub_;
};

BENCHMARK_DEFINE_F(GrpcFixture, TimeXgbInference)(benchmark::State &st) {
  for (auto _ : st) {
    ClientContext context;
    InferResponse response;
    Status status = stub_->InferBatch(&context, request_, &response);
    GOOGLE_CHECK(status.ok());
  }
}

BENCHMARK_REGISTER_F(GrpcFixture, TimeXgbInference)
    ->Threads(1)
    ->Iterations(50)
    ->Repetitions(200)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
