FROM ubuntu:24.10

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/Sao_Paulo

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
    clang-tidy \
    cmake \
    cppcheck \
    curl \
    doxygen \
    gcovr \
    git \
    gnupg \
    libatlas-base-dev \
    libblas-dev \
    libboost-all-dev \
    liblapack-dev \
    ninja-build \
    pkg-config \
    python3.12 \
    software-properties-common \
    unzip \
    zip \
    && apt-get clean && rm -rf /var/lib/apt/lists/*
