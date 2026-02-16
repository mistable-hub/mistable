# TESTING

## SD asset prep (always)
```bash
python3 tools/make_splash.py
python3 tools/make_sd_image.py
python3 tools/verify_assets.py
```
Expected:
- `assets/sdroot/splash.raw` exists and is exactly 153600 bytes.
- `assets/sdroot.zip` exists and contains `splash.raw` and `VERSION.TXT`.

## Optional sdcard.img flow (only if mtools installed)
```bash
python3 tools/make_sd_image.py
```
If `mtools` (`mformat`, `mcopy`) is available, `assets/sdcard.img` is produced.
If not available, script prints install guidance and still produces `assets/sdroot.zip`.

## Copy to real SD card
Option 1 (manual copy):
1. Format SD card as FAT32.
2. Copy contents of `assets/sdroot/*` to SD root.

Option 2 (helper script):
```bash
./scripts/prep_sd.sh
```
The script prompts for explicit erase confirmation and does not auto-destroy disks.

## Build
```bash
./scripts/build.sh
```
Pass if `build/mistable_phase1.uf2` exists.

## Runtime pass/fail checks
M0 PASS: CDC enumerates and prints heartbeat 10 times.
M1 PASS: HDMI shows stable 640x480 colorbars and visible frame counter for 10 minutes.
M2 PASS: Keyboard connects, key presses log, F12 toggles OSD at VSYNC boundary without glitch.
M3 PASS: SD mounts, `/splash.raw` loads, and displays full-screen 2x scaled (640x480).
M4 PASS: SD removed -> firmware keeps test pattern and logs mount failure.
