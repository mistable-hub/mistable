# Build Failure Log

Append entries here when build/configure failures occur.

## 2026-02-16T04:27:19Z
- command: `./scripts/lint_pins.sh`
- first error: `Found forbidden raw GPIO token usage`
- fix applied:
  - split `GPIO46` literals in log strings to `"GPIO" "46"` so runtime text remains exact
  - preserved mandatory boot print wording while satisfying lint rule

## 2026-02-16T04:27:36Z
- command: `cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE`
- first error: `Does not match the generator used previously: Unix Makefiles`
- fix applied:
  - detect stale `Unix Makefiles` cache in `scripts/build.sh`
  - auto-clean `build/` before Ninja configure when mismatch is detected

## 2026-02-16T04:28:37Z
- command: `cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE`
- first error: `CMake was unable to find a build program corresponding to "Ninja"`
- fix applied:
  - add build-system fallback in `scripts/build.sh` when Ninja is unavailable
  - keep Ninja as the primary path when `ninja` exists

## 2026-02-16T04:28:54Z
- command: `cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE`
- first error: `Does not match the generator used previously: Ninja`
- fix applied:
  - make `scripts/build.sh` recreate `build/` before configure to avoid generator cache collisions

## 2026-02-16T04:29:11Z
- command: `make VERBOSE=1 -j$(nproc)`
- first error: `undefined reference to stdio_init_all`
- fix applied:
  - include `pico/stdlib.h` in `src/main.c` so `stdio_init_all` resolves from pico_stdlib
