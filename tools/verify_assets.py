#!/usr/bin/env python3
import os
import sys

checks = [
    ("assets/sdroot/splash.raw", 153600),
    ("assets/sdroot/VERSION.TXT", None),
    ("assets/sdroot.zip", None),
]

ok = True
for path, exact_size in checks:
    if not os.path.isfile(path):
        print(f"ERROR: missing {path}")
        ok = False
        continue
    size = os.path.getsize(path)
    if size == 0:
        print(f"ERROR: empty {path}")
        ok = False
    if exact_size is not None and size != exact_size:
        print(f"ERROR: bad size {path}={size}, expected {exact_size}")
        ok = False

if not ok:
    print("Fix assets with:")
    print("  python3 tools/make_splash.py")
    print("  python3 tools/make_sd_image.py")
    sys.exit(1)

print("OK: assets verified")
