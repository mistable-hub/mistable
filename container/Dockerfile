FROM ubuntu:22.04

RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates \
        git \
        build-essential \
        make \
        verilator \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work
