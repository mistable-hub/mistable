# mistable phase1

Phase 1 RP2350-PiZero appliance layer: DVI 640x480p60 test pattern + frame counter, USB CDC logs, PIO-USB keyboard (F12 OSD toggle), and SD splash loading.

Board name used for build: `waveshare_rp2350_pizero`.

DVI/TMDS deterministic path: Section S4(a), Waveshare baseline present at `third_party/waveshare_demo/01-DVI`.

FatFS deterministic path: Section S6(a), using project-integrated `src/storage/ff_port.*` with 512-byte sector assumptions for Phase 1 mount/read behavior.

Pinned third-party source locations:
- Pico SDK: `third_party/pico-sdk` (submodule, commit `f9478e67602c38f3d1ef2a9de70664d12295e114`)
- FreeRTOS Kernel: `third_party/FreeRTOS-Kernel` (submodule, commit `c9aae9da104b11f3c5e55c5b5e8ede052f51238f`)
- Waveshare demo baseline: `third_party/waveshare_demo` (submodule mirror, commit `a659bc5b6145b2ecded5f3652163b6e05717fa98`)

Build commands:
```bash
mkdir -p build && cd build
cmake .. -G Ninja
ninja
```

Or run:
```bash
./scripts/build.sh
```

Flashing:
1. Enter BOOTSEL mode on RP2350-PiZero.
2. Copy `build/mistable_phase1.uf2` to the mounted device volume.
3. Reboot happens automatically.

SD asset generation:
```bash
python3 tools/make_splash.py
python3 tools/make_sd_image.py
```
