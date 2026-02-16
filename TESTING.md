# Testing

## SD asset generation

Generate splash and SD outputs:

```bash
python3 tools/make_splash.py
python3 tools/make_sd_image.py
```

Expected:
- always creates `assets/sdroot/splash.raw`
- always creates `assets/sdroot.zip`
- creates `assets/sdcard.img` only when `mtools` is installed

## SD card preparation

Workflow 1 (manual copy):
1. Format SD card FAT32.
2. Copy `assets/sdroot/*` to SD card root.

Workflow 2 (image path):
1. If `assets/sdcard.img` exists, write it to SD with your imaging tool.

Helper script:

```bash
./scripts/prep_sd.sh
```

If dependencies are missing, script prints install suggestions and manual fallback.

## Pass/Fail Criteria

- M0 PASS: CDC enumerates and prints heartbeat 10 times.
- M1 PASS: HDMI shows stable colorbars + visible frame counter for 10 minutes.
- M2 PASS: Keyboard connects; key presses logged; F12 toggles OSD without glitch.
- M3 PASS: SD mounts; `splash.raw` loads and displays full-screen 640x480 (2x scale).
- M4 PASS: SD absent test keeps test pattern running and logs mount failure.

Fail any item above => FAIL.
