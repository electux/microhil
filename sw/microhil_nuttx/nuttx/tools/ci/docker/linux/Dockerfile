# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.  The
# ASF licenses this file to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance with the
# License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
# License for the specific language governing permissions and limitations
# under the License.

FROM ubuntu:22.04 AS builder-base
# NOTE WE ARE NOT REMOVEING APT CACHE.
# This should only be used for temp build images that artifacts will be copied from
RUN apt-get update -qq && apt-get install -y -qq \
  curl \
  patch \
  xz-utils

###############################################################################
# Base image that should be used to prepare tools from nuttx-tools
###############################################################################
FROM builder-base AS nuttx-tools

RUN apt-get update -qq && DEBIAN_FRONTEND="noninteractive" apt-get install -y -qq \
  bison \
  cmake \
  flex \
  g++ \
  gawk \
  git \
  gperf \
  libncurses5-dev \
  make

RUN mkdir /tools
WORKDIR /tools

RUN mkdir -p /tools/nuttx-tools
RUN curl -s -L https://bitbucket.org/nuttx/tools/get/9ad3e1ee75c7.tar.gz \
  | tar -C nuttx-tools --strip-components=1 -xz

RUN mkdir bloaty -p \
  && git clone --depth 1 --branch v1.1 https://github.com/google/bloaty bloaty \
  && cd bloaty \
  && cmake -DCMAKE_SYSTEM_PREFIX_PATH=/tools/bloaty \
  && make install

RUN cd nuttx-tools/kconfig-frontends \
  && ./configure --enable-mconf --disable-gconf --disable-qconf --enable-static --prefix=/tools/kconfig-frontends \
  && make install

# Install Rust and targets supported from NuttX
ENV RUST_HOME=/tools/rust
ENV CARGO_HOME=$RUST_HOME/cargo
ENV RUSTUP_HOME=$RUST_HOME/rustup
RUN mkdir -p $CARGO_HOME \
  && curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y \
  && $CARGO_HOME/bin/rustup target add thumbv6m-none-eabi \
  && $CARGO_HOME/bin/rustup target add thumbv7m-none-eabi

CMD [ "/bin/bash" ]

###############################################################################
# Base image that should be used to prepare arch build images
###############################################################################
FROM builder-base AS nuttx-toolchain-base

RUN mkdir /tools
WORKDIR /tools

# Download the latest ARM GCC toolchain prebuilt by ARM
RUN mkdir gcc-arm-none-eabi && \
  curl -s -L  "https://developer.arm.com/-/media/Files/downloads/gnu/12.3.rel1/binrel/arm-gnu-toolchain-12.3.rel1-x86_64-arm-none-eabi.tar.xz" \
  | tar -C gcc-arm-none-eabi --strip-components 1 -xJ

###############################################################################
# Build image for tool required by WASM builds
###############################################################################
FROM nuttx-toolchain-base AS nuttx-toolchain-wasm
# Download the latest WASI-enabled WebAssembly C/C++ toolchain prebuilt by WASM
RUN mkdir wasi-sdk && \
  curl -s -L  "https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-19/wasi-sdk-19.0-linux.tar.gz" \
  | tar -C wasi-sdk --strip-components 1 -xz

# Download the latest "wamrc" AOT compiler prebuilt by WAMR
RUN mkdir wamrc && \
  curl -s -L  "https://github.com/bytecodealliance/wasm-micro-runtime/releases/download/WAMR-1.1.2/wamrc-1.1.2-x86_64-ubuntu-20.04.tar.gz" \
  | tar -C wamrc -xz

###############################################################################
# Final Docker image used for running CI system.  This includes all toolchains
# supported by the CI system.
###############################################################################
FROM ubuntu:22.04
LABEL maintainer="dev@nuttx.apache.org"

RUN apt-get update -qq && DEBIAN_FRONTEND="noninteractive" apt-get install -y -qq \
  build-essential \
  curl \
  gcc \
  libssl-dev

RUN mkdir -p cmake && \
    curl -s -L wget https://cmake.org/files/v3.26/cmake-3.26.0.tar.gz \
    | tar -C cmake --strip-components=1 -xz && \
    cd cmake && ./bootstrap && make && make install && rm -rf cmake

RUN dpkg --add-architecture i386
# This is used for the final images so make sure to not store apt cache
# Note: xtensa-esp32-elf-gdb is linked to libpython2.7
RUN apt-get update -qq && DEBIAN_FRONTEND="noninteractive" apt-get install -y -qq --no-install-recommends \
  -o APT::Immediate-Configure=0 \
  ccache \
  gcc-multilib \
  genromfs \
  gettext \
  git \
  lib32z1-dev \
  libasound2-dev libasound2-dev:i386 \
  libc6-dev-i386 \
  libcurl4-openssl-dev \
  libmp3lame-dev:i386 \
  libmad0-dev:i386 \
  libncurses5-dev \
  libpulse-dev libpulse-dev:i386 \
  libpython2.7 \
  libtinfo5 \
  libusb-1.0-0-dev libusb-1.0-0-dev:i386 \
  libv4l-dev libv4l-dev:i386 \
  libx11-dev libx11-dev:i386 \
  libxext-dev libxext-dev:i386 \
  linux-headers-generic \
  linux-libc-dev:i386 \
  ninja-build \
  qemu-system-arm \
  qemu-system-misc \
  python3 \
  python3-pip \
  python-is-python3 \
  u-boot-tools \
  unzip \
  wget \
  xxd \
  && rm -rf /var/lib/apt/lists/*

# Configure out base setup for adding python packages
ENV PIP_DISABLE_PIP_VERSION_CHECK=true
# This disables the cache with value 0. We do not want caching as it
# increases the images size.
ENV PIP_NO_CACHE_DIR=0
# We are using the minimal python installation from the system so include
# setuptools and also wheel so we can use the binary releases of packages
# instead of requiring them to be compiled.
RUN pip3 install setuptools
RUN pip3 install wheel
RUN pip3 install cmake-format
# Install CodeChecker and use it to statically analyze the code.
# RUN pip3 install CodeChecker
# Install cvt2utf to check for non-UTF characters.
RUN pip3 install cvt2utf
# Install pytest
RUN pip3 install cxxfilt
RUN pip3 install imgtool
RUN pip3 install kconfiglib
RUN pip3 install pexpect==4.8.0
RUN pip3 install pyelftools
RUN pip3 install pyserial==3.5
RUN pip3 install pytest==6.2.5
RUN pip3 install pytest-json==0.4.0
RUN pip3 install pytest-ordering==0.6
RUN pip3 install pytest-repeat==0.9.1

# Used to generate symbol table files

RUN mkdir /tools
WORKDIR /tools

# Pull in the tools we just built for nuttx
COPY --from=nuttx-tools /tools/bloaty/ bloaty/
ENV PATH="/tools/bloaty/bin:$PATH"
COPY --from=nuttx-tools /tools/kconfig-frontends/ kconfig-frontends/
ENV PATH="/tools/kconfig-frontends/bin:$PATH"

# Pull in the Rust toolchain including supported targets
COPY --from=nuttx-tools /tools/rust/ /tools/rust/
ENV CARGO_HOME=/tools/rust/cargo
ENV RUSTUP_HOME=/tools/rust/rustup
ENV PATH="/tools/rust/cargo/bin:$PATH"

COPY --from=nuttx-toolchain-arm /tools/gcc-arm-none-eabi/ gcc-arm-none-eabi/
ENV PATH="/tools/gcc-arm-none-eabi/bin:$PATH"

# WASI-enabled WebAssembly C/C++ toolchain
COPY --from=nuttx-toolchain-wasm /tools/wasi-sdk/ wasi-sdk/
ENV WASI_SDK_PATH="/tools/wasi-sdk"
ENV PATH="/tools/wamr:$PATH"

# Configure ccache
RUN mkdir -p /tools/ccache/bin && \
  ln -sf `which ccache` /tools/ccache/bin/arm-none-eabi-gcc && \
  ln -sf `which ccache` /tools/ccache/bin/arm-none-eabi-g++ && \
  ln -sf `which ccache` /tools/ccache/bin/gcc && \
  ln -sf `which ccache` /tools/ccache/bin/g++

ENV PATH="/tools/ccache/bin:$PATH"

CMD [ "/bin/bash" ]
