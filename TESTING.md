# Testing

## SD Asset Generation

1. Generate splash.raw:
   ```bash
   python3 tools/make_splash.py
   ```
2. Generate sdroot.zip (always) and sdcard.img (only if mtools present):
   ```bash
   python3 tools/make_sd_image.py
   ```

## SD Card Prep

Option A (manual copy):
1. Format a microSD card as FAT32.
2. Copy `assets/sdroot/*` to the SD card root.

Option B (image):
1. If `assets/sdcard.img` exists, flash it to a microSD card with your preferred tool.

## Pass/Fail Criteria

M0: CDC enumerates and prints heartbeat 10 times.

M1: HDMI shows stable colorbars + visible frame counter for 10 minutes.

M2: Keyboard connects; key presses logged; F12 toggles OSD without glitch.

M3: SD mounts; splash.raw loads and displays full-screen 640x480 (2x scale).

M4: SD absent test: remove SD and confirm firmware continues with test pattern and logs mount failure.
