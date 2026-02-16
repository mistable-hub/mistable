# mistable Phase 1

RP2350-PiZero appliance layer firmware skeleton for:
- DVI 640x480p60 path
- USB CDC logging
- PIO-USB keyboard host
- OSD toggle (F12)
- SD splash loader

## Deterministic source selection
- DVI/TMDS path: (a) Waveshare baseline expected under `third_party/waveshare_demo/01-DVI`.
- USB host baseline: Waveshare baseline expected under `third_party/waveshare_demo/PIO-USB`.
- FatFS path: (a) Pico SDK integration.

## Pinned submodule SHAs
- Pico SDK: `f9478e67602c38f3d1ef2a9de70664d12295e114`
- FreeRTOS-Kernel: `c9aae9da104b11f3c5e55c5b5e8ede052f51238f`

## Board
Build uses `-DPICO_BOARD=waveshare_rp2350_pizero`.

## Build
```bash
mkdir -p build && cd build
cmake .. -G Ninja
ninja
```
The helper script uses `-DPICO_BOARD=waveshare_rp2350_pizero`.

## Flash UF2
1. Hold BOOTSEL while connecting the board.
2. Copy `build/mistable_phase1.uf2` to the mounted USB mass-storage device.

See `TESTING.md` for M0-M4 checks and SD workflows.
