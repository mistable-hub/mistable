#!/usr/bin/env bash
set -euo pipefail

rm -rf build

./scripts/docker.sh make sim

if [[ ! -s build/frame.ppm ]]; then
  echo "ERROR: build/frame.ppm missing or empty"
  exit 1
fi

echo "PASS: build/frame.ppm generated"
