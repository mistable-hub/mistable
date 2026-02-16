# Build failure log

Append entries here when build failures are encountered and fixed.

## 2026-02-16T04:04:15Z
- command: cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE
- first error: CMake Error: CMake was unable to find a build program corresponding to "Ninja".  CMAKE_MAKE_PROGRAM is not set.  You probably need to select a different build tool.
- fix applied:
  - add generator/toolchain detection in scripts/build.sh
  - fallback to Unix Makefiles when Ninja is unavailable

## 2026-02-16T04:04:49Z
- command: ./scripts/test.sh
- first error: CMakeFiles/mistable_phase1.dir/build.make:76: *** missing separator.  Stop.
- fix applied:
  - replace shell-redirection custom command in pico_generate_pio_header
  - generate PIO headers at configure-time with CMake file(WRITE)
