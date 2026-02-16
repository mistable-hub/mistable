# mistable Phase 1 RP2350-PiZero appliance

Scope in this phase:
- DVI-over-HDMI 640x480p60 with colorbars and frame counter
- USB CDC ACM logging on PRIMARY USB-C
- USB host HID keyboard on SECOND USB-C (PIO-USB GPIO46/47)
- F12 toggled OSD applied at VSYNC boundary
- SD FAT mount via SPI0 and `/splash.raw` load/display (320x240 RGB565 scaled 2x)

Out of scope:
- FPGA ingest
- audio
- EDID/DDC
- CEC
- HPD
- mouse
- joypads

Board setting used by build scripts:
- `PICO_BOARD=waveshare_rp2350_pizero`

Deterministic dependency paths:
- Pico SDK: `third_party/pico-sdk/` pinned revision `local-pinned-2026-02-16-0001`
- FreeRTOS kernel: `third_party/FreeRTOS-Kernel/` pinned local source snapshot
- DVI/TMDS path: S4(b), baseline path `third_party/PicoDVI_or_TMDS/`
- FatFS path: S6(b), vendored at `third_party/FatFS/`

## Build

```bash
mkdir -p build && cd build
cmake .. -G Ninja
ninja
```

Or run the gated build script:

```bash
./scripts/build.sh
```

## Flash UF2

1. Enter BOOTSEL mode on the board.
2. Copy `build/mistable_phase1.uf2` to the USB mass storage device.
3. Device reboots into firmware.

See `scripts/flash_uf2.txt` for the same steps.
