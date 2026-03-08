FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    build-essential \
    make \
    verilator \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /work
