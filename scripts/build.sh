#!/usr/bin/env bash
set -euo pipefail

DEFAULT_BOARD="waveshare_rp2350_pizero"

if [[ -d third_party/pico-sdk && -z "$(ls -A third_party/pico-sdk)" ]]; then
  echo "ERROR: third_party/pico-sdk is empty. Run: git submodule update --init --recursive"
  exit 1
fi
if [[ -d third_party/FreeRTOS-Kernel && -z "$(ls -A third_party/FreeRTOS-Kernel)" ]]; then
  echo "ERROR: third_party/FreeRTOS-Kernel is empty. Run: git submodule update --init --recursive"
  exit 1
fi
if [[ -d third_party/waveshare_demo && -z "$(ls -A third_party/waveshare_demo)" ]]; then
  echo "ERROR: third_party/waveshare_demo is empty. Run: git submodule update --init --recursive"
  exit 1
fi

scripts/lint_pins.sh
python3 tools/verify_assets.py

rm -rf build
mkdir -p build
cd build
if command -v ninja >/dev/null 2>&1; then
  cmake .. -G Ninja -DPICO_BOARD="${DEFAULT_BOARD}"
  ninja -v
else
  echo "WARNING: Ninja not found, falling back to Unix Makefiles."
  echo "Install Ninja (Ubuntu: sudo apt-get install ninja-build) to use the required default flow."
  cmake .. -G "Unix Makefiles" -DPICO_BOARD="${DEFAULT_BOARD}"
  make VERBOSE=1
fi
