#include <benchmark/benchmark.h>
#include <grpcpp/grpcpp.h>

#include <iostream>
#include <random>
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

thread_local std::random_device r;
thread_local std::mt19937 rand_gen(r());
thread_local std::uniform_int_distribution<uint32_t> unif_int(0, 2);
thread_local std::uniform_real_distribution<float> unif_float(0, 100);

InferRequestItem GenRandomItem() {
  InferRequestItem i;
  const std::vector<std::string> choices{"asdf", "m", "f"};
  const std::string &s = choices[unif_int(rand_gen)];
  const float age = unif_float(rand_gen);
  i.set_id(std::to_string(rand_gen()));
  {
    Feature f;
    f.set_f32_value(age);
  }
  {
    Feature f;
    f.set_str_value(s);
    (*i.mutable_features())["gender"] = f;
  }
  return i;
}

InferRequest GenRequest(size_t batch_size) {
  InferRequest request;
  request.set_model("exp1_net");
  for (int i = 0; i < batch_size; ++i) {
    request.mutable_requests()->Add(GenRandomItem());
  }
  return request;
}

class GrpcFixture : public benchmark::Fixture {
 public:
  void SetUp(const ::benchmark::State &state) override {
    request_ = GenRequest(state.range(0));
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
    GOOGLE_CHECK(status.ok()) << status.error_details();
  }
}

BENCHMARK_REGISTER_F(GrpcFixture, TimeXgbInference)
    ->Threads(1)
    ->Iterations(10)
    ->Repetitions(100)
    ->Range(1, 1024)
    ->RangeMultiplier(2)
    ->DisplayAggregatesOnly()
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
