# Build Failure Log

Append entries for each configure/build failure with:
- Timestamp
- Command
- First error line
- Fix applied

## 2026-02-16T05:49:46Z
- Command: `./scripts/build.sh`
- First error: `ERROR: missing required dependency path: third_party/pico-sdk/pico_sdk_init.cmake`
- Fix applied:
  - Added deterministic pre-build submodule presence checks in `scripts/build.sh`.
  - Added dependency guidance (`git submodule update --init --recursive`) and non-zero exit.

## 2026-02-16T05:50:17Z
- Command: `./scripts/test.sh`
- First error: `ERROR: missing required dependency path: third_party/pico-sdk/pico_sdk_init.cmake`
- Fix applied:
  - No code change; environment remains blocked until required submodules are fetched.

## 2026-02-16T05:50:31Z
- Command: `cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE`
- First error: `Pico SDK not found at /workspaces/mistable/third_party/pico-sdk`
- Fix applied:
  - `pico_sdk_import.cmake` now emits deterministic hard-fail guidance to run submodule init.
