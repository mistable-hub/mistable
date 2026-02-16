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

## 2026-02-16T05:57:33Z
- Command: `./scripts/build.sh`
- First error: `ERROR: missing required dependency path: third_party/pico-sdk/pico_sdk_init.cmake`
- Fix applied:
  - Re-ran required submodule sync/init commands (`git submodule sync --recursive`, `git submodule update --init --recursive`).
  - No repository-side code fix possible in offline environment; build remains blocked until `third_party/pico-sdk` is populated.

## 2026-02-16T05:58:24Z
- Command: `rm -rf build && mkdir build && cd build && cmake .. -G Ninja && ninja -v`
- First error: `Pico SDK not found at /workspaces/mistable/third_party/pico-sdk`
- Fix applied:
  - Reconfirmed deterministic dependency failure path after clean rebuild.
  - No additional code changes made; requires populated `third_party/pico-sdk` content.

## 2026-02-16T06:04:39Z
- Command: `cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE`
- First error: `add_subdirectory given source "/workspaces/mistable/../src" which is not an existing directory`
- Fix applied:
  - Fixed mock Pico SDK path derivation in `third_party/pico-sdk/cmake/pico_sdk_init.cmake`.
  - Re-routed `add_subdirectory` to use an absolute SDK root computed at include time.
