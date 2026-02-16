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
Run these after submodules are initialized:
- `git -C third_party/pico-sdk rev-parse HEAD`
- `git -C third_party/FreeRTOS-Kernel rev-parse HEAD`

## Board
Build uses `-DPICO_BOARD=waveshare_rp2350_pizero`.

## Build
```bash
mkdir -p build && cd build
cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero
ninja
```

## Flash UF2
1. Hold BOOTSEL while connecting the board.
2. Copy `build/mistable_phase1.uf2` to the mounted USB mass-storage device.

See `TESTING.md` for M0-M4 checks and SD workflows.
