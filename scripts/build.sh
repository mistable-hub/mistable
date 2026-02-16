#!/usr/bin/env bash
set -euo pipefail

required=(
  third_party/pico-sdk/pico_sdk_init.cmake
  third_party/pico-sdk/external/pico_sdk_import.cmake
  third_party/FreeRTOS-Kernel/include/FreeRTOS.h
  third_party/waveshare_demo/README.md
  third_party/waveshare_demo/01-DVI
  third_party/waveshare_demo/PIO-USB
)

missing=0
for p in "${required[@]}"; do
  if [[ ! -e "$p" ]]; then
    echo "ERROR: missing required dependency path: $p"
    missing=1
  fi
done

if [[ "$missing" -ne 0 ]]; then
  echo "Run: git submodule update --init --recursive"
  exit 1
fi

./scripts/lint_pins.sh
python3 tools/verify_assets.py

mkdir -p build
cd build
cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero
ninja -v
