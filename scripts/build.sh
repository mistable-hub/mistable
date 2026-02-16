#!/usr/bin/env bash
set -euo pipefail

if [[ ! -f third_party/pico-sdk/pico_sdk_init.cmake ]]; then
  echo "Missing required file: third_party/pico-sdk/pico_sdk_init.cmake"
  echo "git submodule update --init --recursive"
  exit 1
fi
if [[ ! -f third_party/pico-sdk/external/pico_sdk_import.cmake ]]; then
  echo "Missing required file: third_party/pico-sdk/external/pico_sdk_import.cmake"
  echo "git submodule update --init --recursive"
  exit 1
fi
if [[ ! -f third_party/FreeRTOS-Kernel/include/FreeRTOS.h ]]; then
  echo "Missing required file: third_party/FreeRTOS-Kernel/include/FreeRTOS.h"
  echo "git submodule update --init --recursive"
  exit 1
fi
if [[ ! -f third_party/waveshare_demo/README.md ]]; then
  echo "Missing required file: third_party/waveshare_demo/README.md"
  echo "git submodule update --init --recursive"
  exit 1
fi
if [[ ! -d third_party/waveshare_demo/01-DVI ]]; then
  echo "Missing required directory: third_party/waveshare_demo/01-DVI"
  echo "git submodule update --init --recursive"
  exit 1
fi
if [[ ! -d third_party/waveshare_demo/PIO-USB ]]; then
  echo "Missing required directory: third_party/waveshare_demo/PIO-USB"
  echo "git submodule update --init --recursive"
  exit 1
fi

./scripts/lint_pins.sh
python3 tools/verify_assets.py

if ! command -v ninja >/dev/null 2>&1; then
  echo "Missing dependency: ninja"
  echo "Install: sudo apt-get install ninja-build"
  exit 1
fi

mkdir -p build
cd build
cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero
ninja -v
