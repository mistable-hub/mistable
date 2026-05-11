FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    ca-certificates \
    curl \
    git \
    build-essential \
    make \
    verilator \
    xz-utils \
 && rm -rf /var/lib/apt/lists/*

RUN curl -fsSL https://nodejs.org/dist/v22.13.1/node-v22.13.1-linux-x64.tar.xz \
    | tar -xJ -C /usr/local --strip-components=1

RUN npm config set prefix /usr/local \
 && npm install -g @anthropic-ai/claude-code

WORKDIR /work
