# Phase 1 Test Matrix

## Asset generation
```bash
python3 tools/make_splash.py
python3 tools/make_sd_image.py
python3 tools/verify_assets.py
```

`tools/make_sd_image.py` always emits `assets/sdroot.zip`. If `mtools` is installed, it also emits `assets/sdcard.img`.

## Prepare real SD card
Workflow 1 (manual): format SD as FAT32 and copy all files from `assets/sdroot/` to the SD root.

Workflow 2 (image): if `assets/sdcard.img` exists, write it to SD using your preferred imaging utility.

## Build and flash
```bash
./scripts/build.sh
```
Flash using steps in `scripts/flash_uf2.txt`.

## Pass/fail
- M0: CDC enumerates and prints heartbeat 10 times.
- M1: HDMI shows stable colorbars + visible frame counter for 10 minutes.
- M2: Keyboard connects; key presses logged; F12 toggles OSD without glitch.
- M3: SD mounts; `/splash.raw` loads and displays full-screen 640x480 (2x scale).
- M4: SD absent; firmware continues with test pattern and logs mount failure.
