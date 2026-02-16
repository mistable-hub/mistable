#!/usr/bin/env bash
set -euo pipefail

if [[ ! -f .gitmodules ]]; then
  echo "Missing .gitmodules"
  exit 1
fi

status_output="$(git submodule status || true)"
echo "$status_output"
if echo "$status_output" | grep -Eq '^[[:space:]]*-' ; then
  echo "Submodules are not initialized. Run: git submodule update --init --recursive"
  exit 1
fi

if [[ ! -d third_party/pico-sdk && -z "${PICO_SDK_PATH:-}" ]]; then
  echo "Pico SDK missing. Initialize submodules or set PICO_SDK_PATH"
  exit 1
fi

scripts/lint_pins.sh
scripts/lint_forbidden.sh
python3 tools/verify_assets.py

rm -rf build
mkdir -p build
cd build
if command -v ninja >/dev/null 2>&1; then
  cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero
  ninja -v
else
  echo "Ninja not found; falling back to Unix Makefiles for this environment"
  cmake .. -G "Unix Makefiles" -DPICO_BOARD=waveshare_rp2350_pizero
  make VERBOSE=1 -j"$(nproc)"
fi
