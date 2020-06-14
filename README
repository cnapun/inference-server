# Inference Server
[very hacky, not practical yet] Basic C++ model inference server using GRPC.
Currently isn't async on the server side I believe. Currently only xgboost is
supported; pytorch will probably come in the future

### Running
The only external dependency should be xgboost (tested with 1.1.1) and bazel (tested with 3.2.0)

To run server, `bazel run //cpp/server:inference_server -- --port 10101`
to run client, `bazel run //cpp/client:inference_client`

### Code formatting
Files are currently formatted by
```
find . -iname *.h -o -iname *.cc | xargs clang-format -i
find . -iname BUILD | xargs buildifier
```
