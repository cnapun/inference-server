#include <gflags/gflags.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <iostream>
#include <memory>

#include "cpp/server/model_pool.h"
#include "proto/inference.grpc.pb.h"
#include "proto/inference.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using inference::Feature;
using inference::InferRequest;
using inference::InferRequestItem;
using inference::InferResponse;
using inference::ModelInference;

DEFINE_int32(port, 50051, "Port to run server at");
DEFINE_string(config_file, "data/config.json", "File containing model definitions");
DEFINE_int32(max_threads, 2, "Number of threads for server. Must be >= 2");

class InferenceServiceImpl final : public ModelInference::Service {
 public:
  InferenceServiceImpl() : model_pool_(std::make_unique<models::ModelPool>()) {
    model_pool_->LoadModels(FLAGS_config_file);
  }

  Status InferBatch(ServerContext *context, const InferRequest *request,
                    InferResponse *response) override {
    if (model_pool_->HandleRequest(*request, response)) {
      return Status::OK;
    } else {
      return Status(grpc::StatusCode::INTERNAL, "some random error happened");
    }
  }

 private:
  std::unique_ptr<models::ModelPool> model_pool_;
};

void RunServer() {
  std::string server_address("0.0.0.0:" + std::to_string(FLAGS_port));
  InferenceServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  ServerBuilder builder;
  grpc::ResourceQuota resource_quota;
  resource_quota.SetMaxThreads(FLAGS_max_threads);
  builder.SetResourceQuota(resource_quota);
  builder.SetSyncServerOption(ServerBuilder::SyncServerOption::MAX_POLLERS, FLAGS_max_threads);
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  RunServer();

  return 0;
}
