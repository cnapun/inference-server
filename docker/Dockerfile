FROM ubuntu:18.04 AS build-env
RUN apt-get update && apt-get install -y \
   zip \
   unzip \
   build-essential \
   wget \
   curl \
   libssl-dev \
   gnupg \
   git \
   && rm -rf /var/lib/apt/lists/*

RUN curl https://bazel.build/bazel-release.pub.gpg | apt-key add - \
   && echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN apt-get update \
   && apt-get install -y bazel-3.2.0 \
   && ln -s /usr/bin/bazel-3.2.0 /usr/bin/bazel \
   && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/Kitware/CMake/releases/download/v3.17.2/cmake-3.17.2-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/cmake-install.sh

ENV PATH="/usr/bin/cmake/bin:${PATH}"
ENV CMAKE_CXX_COMPILER=/usr/bin/g++
ENV CMAKE_C_COMPILER=/usr/bin/gcc

WORKDIR /external/ninja
RUN git init \
    && git remote add origin https://github.com/ninja-build/ninja.git \
    && git fetch origin ed7f67040b370189d989adbd60ff8ea29957231f \
    && git reset --hard FETCH_HEAD \
    && cmake -Bbuild-cmake -H. -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build-cmake

ENV PATH="/external/ninja/build-cmake:${PATH}"

WORKDIR /src
COPY . .

RUN bazel build -c opt --jobs=4 //cpp/server

RUN mkdir /inference_server/ \
    && ldd bazel-bin/cpp/server/server | grep "=> /" | awk '{print $3}' | xargs -I '{}' cp -v '{}' /inference_server/ \
    && cp bazel-bin/cpp/server/server /inference_server/server \
    && cp -r /src/data /data
ENV LD_LIBRARY_PATH=/inference_server
ENTRYPOINT ["/bin/bash"]

FROM ubuntu:18.04
COPY --from=build-env /inference_server/ /inference_server/
COPY --from=build-env /data /data
ENV LD_LIBRARY_PATH=/inference_server
ENTRYPOINT ["/inference_server/server" ]