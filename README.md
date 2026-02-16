# mistable Phase 1 RP2350-PiZero Appliance Layer

Board name used for build: `waveshare_rp2350_pizero`

DVI/TMDS dependency path: S4(a) Waveshare baseline from `third_party/waveshare_demo/01-DVI`
USB host baseline path: `third_party/waveshare_demo/PIO-USB`
FatFS path: Pico SDK integration path (project-side ff_port shim for mount/read flow)

## Build

```bash
mkdir -p build && cd build
cmake .. -G Ninja
ninja
```

Or run the enforced pipeline:

```bash
./scripts/build.sh
```

## Flash

- Enter BOOTSEL mode on RP2350-PiZero.
- Copy `build/mistable_phase1.uf2` to the mounted mass-storage device.
- See `scripts/flash_uf2.txt`.

## Submodules

```text
 c9aae9da104b11f3c5e55c5b5e8ede052f51238f third_party/FreeRTOS-Kernel (heads/main)
 f9478e67602c38f3d1ef2a9de70664d12295e114 third_party/pico-sdk (heads/main)
 a659bc5b6145b2ecded5f3652163b6e05717fa98 third_party/waveshare_demo (heads/main)
```

Pico SDK SHA: `f9478e67602c38f3d1ef2a9de70664d12295e114`
FreeRTOS-Kernel SHA: `c9aae9da104b11f3c5e55c5b5e8ede052f51238f`
Waveshare demo SHA: `a659bc5b6145b2ecded5f3652163b6e05717fa98`
