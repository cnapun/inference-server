# Inference Server
This is mildly hacky, not practical yet. Basic C++ model inference server using GRPC. Currently only xgboost is supported; Pytorch might come in the future.

### Running
The only external dependencies should be xgboost (tested with 1.1.1) and bazel (tested with 3.2.0)

To run server, `bazel run //cpp/server -- --port 50051`
to run client, `bazel run //cpp/client:inference_client -- --port 50051`

### Code formatting
Files are currently formatted by
```
find . -iname *.h -o -iname *.cc | xargs clang-format -i
find . -iname BUILD | xargs buildifier
```
