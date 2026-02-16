# TESTING

## Asset generation
```bash
python3 tools/make_splash.py
python3 tools/make_sd_image.py
```
Always expected:
- `assets/sdroot/splash.raw`
- `assets/sdroot.zip`

If `mtools` is installed, also expected:
- `assets/sdcard.img`

## Copy to real SD card
Workflow 1:
- Format SD as FAT32
- Copy `assets/sdroot/*` to SD root

Workflow 2 (if `assets/sdcard.img` exists):
- Write image with your preferred imaging tool

Or use:
```bash
./scripts/prep_sd.sh
```

## Pass/Fail matrix
- M0 PASS: CDC enumerates and heartbeat prints 10 times.
- M1 PASS: HDMI shows stable 640x480 colorbars with visible frame counter for 10 minutes.
- M2 PASS: Keyboard hotplug works, keypress logs appear, F12 toggles OSD at VSYNC boundary.
- M3 PASS: SD mounts and `/splash.raw` displays full-screen (2x 320x240 to 640x480).
- M4 PASS: without SD, system continues on test pattern and logs mount failure.

Fail criteria:
- Missing CDC output, unstable video, OSD tearing, crash on keyboard hotplug, or SD failure not logged.
