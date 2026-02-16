# Testing

## Build

```bash
./scripts/test.sh
```

## SD asset generation (always)

```bash
python3 tools/make_splash.py
python3 tools/make_sd_image.py
```

Expected:
- `assets/sdroot/splash.raw` exists, exactly 153600 bytes.
- `assets/sdroot.zip` exists and contains `splash.raw` and `VERSION.TXT` at root.

## Optional sdcard.img (only if mtools is installed)

`python3 tools/make_sd_image.py` will also create `assets/sdcard.img` when `mformat` and `mcopy` are present.

If mtools is missing:
- install with `sudo apt-get install -y mtools`, or
- manually copy `assets/sdroot/*` to a FAT32 SD card root.

## Prepare a real SD card

```bash
./scripts/prep_sd.sh
```

The script prompts for explicit confirmation before formatting.

## Pass/Fail matrix

- M0 pass: CDC enumerates and prints heartbeat 10 times.
- M1 pass: HDMI shows stable colorbars + visible frame counter for 10 minutes.
- M2 pass: keyboard connect + key logs + F12 OSD toggle at VSYNC boundary without visible glitch.
- M3 pass: SD mounts and `splash.raw` displays full-screen 640x480 using 2x scale.
- M4 pass: no SD keeps test pattern and mount errors continue in logs.
