# mistable phase1

Phase 1 appliance layer for RP2350-PiZero: DVI 640x480p60, CDC logging, PIO-USB keyboard, OSD, and SD splash.

## Build

```bash
mkdir -p build && cd build
cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero
ninja
```

Or run:

```bash
./scripts/build.sh
```

## Flash

1) Enter BOOTSEL.
2) Copy `build/mistable_phase1.uf2` to the mass storage device.

## Dependencies

- Pico SDK: vendored stub at `third_party/pico-sdk` (revision: 2d9ff46d02fa8790157d9add081cb3142ee27d25)
- FreeRTOS-Kernel: vendored stub at `third_party/FreeRTOS-Kernel` (revision: 38416d599344c32ff0b1943d5ee7656e025db351)
- FatFS: Pico SDK stub integration at `third_party/pico-sdk/src/rp2_common/pico_fatfs`

## DVI/TMDS Baseline

Using deterministic path (b): `third_party/PicoDVI_or_TMDS`.
