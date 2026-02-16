#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)

"${ROOT_DIR}/scripts/lint_pins.sh"
python3 "${ROOT_DIR}/tools/verify_assets.py"

if [[ -z "${PICO_SDK_PATH:-}" ]]; then
  if [[ -d "${ROOT_DIR}/third_party/pico-sdk" ]]; then
    export PICO_SDK_PATH="${ROOT_DIR}/third_party/pico-sdk"
  else
    echo "ERROR: PICO_SDK_PATH not set and third_party/pico-sdk missing." >&2
    exit 1
  fi
fi

if [[ ! -f "${PICO_SDK_PATH}/pico_sdk_init.cmake" ]]; then
  echo "ERROR: Pico SDK not found at ${PICO_SDK_PATH}." >&2
  exit 1
fi

BUILD_DIR="${ROOT_DIR}/build"
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

if command -v ninja >/dev/null 2>&1; then
  if [[ -f CMakeCache.txt ]] && grep -q "CMAKE_GENERATOR:INTERNAL=Unix Makefiles" CMakeCache.txt; then
    cd "${ROOT_DIR}" && rm -rf "${BUILD_DIR}" && mkdir -p "${BUILD_DIR}" && cd "${BUILD_DIR}"
  fi
  cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero
  ninja
else
  echo "Ninja not found; falling back to Unix Makefiles. Install ninja to use the recommended generator." >&2
  if [[ -f CMakeCache.txt ]] && grep -q "CMAKE_GENERATOR:INTERNAL=Ninja" CMakeCache.txt; then
    cd "${ROOT_DIR}" && rm -rf "${BUILD_DIR}" && mkdir -p "${BUILD_DIR}" && cd "${BUILD_DIR}"
  fi
  cmake .. -G "Unix Makefiles" -DPICO_BOARD=waveshare_rp2350_pizero
  make
fi
