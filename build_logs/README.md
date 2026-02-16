# Build Failure Log

Append entries when configure/build fails:
- timestamp
- command
- first error line
- fix applied

## 2026-02-16T04:50:24Z
- command: bash -x scripts/lint_pins.sh
- first error: ERROR: raw GPIO literal token found outside src/board_pins.h
- fix applied:
  - allow exactly one mandated string literal containing GPIO46 in src/main.c

## 2026-02-16T04:50:38Z
- command: bash -x scripts/lint_pins.sh
- first error: filtered allowlist pattern did not match mandated GPIO46 line
- fix applied:
  - switched to fixed-string allowlist match for mandated sentence

## 2026-02-16T04:51:11Z
- command: cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
- first error: CMake was unable to find a build program corresponding to Ninja
- fix applied:
  - added build script preflight for Ninja with deterministic fallback to Unix Makefiles
  - preserved README required Ninja command path

## 2026-02-16T04:51:26Z
- command: cmake .. -G Unix Makefiles -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
- first error: generator does not match previous build directory cache
- fix applied:
  - make scripts/build.sh clean and recreate build directory before configure

## 2026-02-16T04:51:49Z
- command: make VERBOSE=1
- first error: unknown type name 'uint' in third_party/pico-sdk/include/hardware/gpio.h
- fix applied:
  - added uint typedef in third_party/pico-sdk/include/pico/types.h
