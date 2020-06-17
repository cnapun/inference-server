![](https://travis-ci.com/cnapun/inference-server.svg?branch=master)
# Inference Server
This is mildly hacky, not practical yet. Basic C++ model inference server using GRPC. Currently only xgboost is supported; Pytorch might come in the future.

### Running

#### On local machine
The only external dependencies should be Bazel (tested with 3.2.0) and CMake (>= 3.13)

To run server, `bazel run //cpp/server -- --port 50051`
to run client, `bazel run //cpp/client -- --port 50051 --model exp1_net` or `bazel run //cpp/client -- --port 50051 --model exp2_net`

#### In docker
There is also a prepackaged docker container with the server (not the client) built.
The model and config should be specified by mounting local directories with the configs
and models, and then a custom config file can be specified with `--config_file`

```shell script
docker pull cnapun/inference-server:latest
docker run -d -p 10101:10101 \
  -v /path/to/data:/data1 \
  --name inference_server \
  cnapun/inference-server:latest \
    --port 10101 \
    --config_file /data1/my_config.json \
    --max_threads 4
```

### Code formatting
Files are currently formatted by
```
find . -iname *.h -o -iname *.cc | xargs clang-format -i
find . -iname BUILD | xargs buildifier
```
