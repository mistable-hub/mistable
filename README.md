# mistable Phase 1 RP2350-PiZero appliance layer

Board: `waveshare_rp2350_pizero`

Deterministic source path:
- DVI/TMDS: path (a) using `third_party/waveshare_demo/01-DVI`
- PIO-USB host: using `third_party/waveshare_demo/PIO-USB`
- FatFS: path (a) using in-repo integration (`src/storage/ff_port.c` for mount/read)

Pinned revisions:
- Pico SDK SHA: `f9478e67602c38f3d1ef2a9de70664d12295e114`
- FreeRTOS-Kernel SHA: `c9aae9da104b11f3c5e55c5b5e8ede052f51238f`

Build:
```bash
mkdir -p build && cd build
cmake .. -G Ninja
ninja
```

Recommended scripted build:
```bash
./scripts/build.sh
```

Flash UF2:
- Enter BOOTSEL on the board.
- Copy `build/mistable_phase1.uf2` to the RP2350 mass storage device.
- See `scripts/flash_uf2.txt`.
