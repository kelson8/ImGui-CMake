ARG UBUNTU_VERSION=24.04
FROM ubuntu:${UBUNTU_VERSION} AS base

# Ubuntu 24.04 compiler for my ImGui-CMake project.

# Set the compilers and versions here
ARG C_COMPILER=gcc
ARG CXX_COMPILER=g++
# https://documentation.ubuntu.com/ubuntu-for-developers/reference/availability/gcc/
ARG COMPILER_VERSION=14
ARG BUILD_TYPE=Release

# https://apt.kitware.com/
# Setup Kitware PPA for Ubuntu 24, this allows me to use newer CMake versions.
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    ca-certificates \
    gpg \
    wget && \
    wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null && \
    echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ noble main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null && \
    apt-get update && \
    apt-get install -y --no-install-recommends kitware-archive-keyring

RUN apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    gcc \
    g++ \
    libglew-dev \
    libglfw3-dev \
    libglfw3 \
    libc6-dev \
    libfreetype6-dev \
    libspdlog-dev \
    make \
    gdb \
    git \
    xorg-dev \
    ${C_COMPILER}-${COMPILER_VERSION} \
    ${CXX_COMPILER}-${COMPILER_VERSION} && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

FROM base AS build

WORKDIR /app

COPY . ./source

RUN cd /app/source && git submodule init && git submodule update --init 

# Build the project
RUN cd /app/source && cmake -B build && cmake --build build --parallel

# Remove all source files, and keep the bin folder intact.
RUN mv ./source/bin/ /app/ && \ 
    rm -R ./source
    

