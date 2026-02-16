#!/usr/bin/env python3
import os
import sys

checks = [
    ("assets/sdroot/splash.raw", 153600),
    ("assets/sdroot/VERSION.TXT", None),
    ("assets/sdroot.zip", None),
]

ok = True
for path, size in checks:
    if not os.path.exists(path):
        print(f"ERROR: missing {path}")
        ok = False
        continue
    if size is not None and os.path.getsize(path) != size:
        print(f"ERROR: {path} size is {os.path.getsize(path)}, expected {size}")
        ok = False

if not ok:
    print("Fix assets by running: python3 tools/make_splash.py && python3 tools/make_sd_image.py")
    sys.exit(1)

print("Asset verification passed.")
