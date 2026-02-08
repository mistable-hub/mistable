#!/usr/bin/env bash
set -euo pipefail

rm -rf build

make sim

if [[ ! -f build/frame.ppm ]]; then
  echo "ERROR: build/frame.ppm not found"
  exit 1
fi

echo "SUCCESS: build/frame.ppm generated"
