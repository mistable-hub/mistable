#!/usr/bin/env bash
set -euo pipefail

required=(
  pico_sdk_import.cmake
  src/FreeRTOSConfig.h
  src/storage/ffconf.h
  src/video/tmds.pio
  src/usb/piousb_host.pio
  assets/sdroot/splash.raw
  assets/sdroot/VERSION.TXT
  assets/sdroot.zip
)

for f in "${required[@]}"; do
  if [[ ! -s "$f" ]]; then
    echo "ERROR: required file missing or empty: $f"
    exit 1
  fi
done

if [[ ! -d third_party/pico-sdk && -z "${PICO_SDK_PATH:-}" ]]; then
  echo "ERROR: pinned Pico SDK missing and PICO_SDK_PATH not set"
  exit 1
fi

scripts/lint_pins.sh
python3 tools/verify_assets.py

if grep -RInE 'TODO|FIXME|stub|not implemented|return[[:space:]]+0;[[:space:]]*/\*[[:space:]]*TEMP' src; then
  echo "ERROR: placeholder marker found in src/"
  exit 1
fi

rm -rf build
mkdir -p build
cd build

generator="Ninja"
builder_cmd=(ninja -v)
if ! command -v ninja >/dev/null 2>&1; then
  generator="Unix Makefiles"
  builder_cmd=(make VERBOSE=1 -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)")
  echo "INFO: ninja not found, using Unix Makefiles fallback"
fi

if ! command -v cc >/dev/null 2>&1 && ! command -v gcc >/dev/null 2>&1; then
  echo "ERROR: no C compiler found. Install build-essential (Debian/Ubuntu)."
  exit 1
fi

cmake .. -G "${generator}" -DPICO_BOARD=waveshare_rp2350_pizero
"${builder_cmd[@]}"

if [[ ! -s generated/pio/tmds.pio.h ]]; then
  echo "ERROR: missing generated PIO header generated/pio/tmds.pio.h"
  exit 1
fi
if [[ ! -s generated/pio/piousb_host.pio.h ]]; then
  echo "ERROR: missing generated PIO header generated/pio/piousb_host.pio.h"
  exit 1
fi

if [[ ! -s mistable_phase1.uf2 || ! -s mistable_phase1.elf ]]; then
  echo "ERROR: output artifacts missing"
  exit 1
fi

cd ..
if grep -RInE 'TODO|FIXME|stub|not implemented|return[[:space:]]+0;[[:space:]]*/\*[[:space:]]*TEMP' src; then
  echo "ERROR: placeholder marker found in src/ after build"
  exit 1
fi

echo "OK: build complete"
