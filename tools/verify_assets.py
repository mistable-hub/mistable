#!/usr/bin/env python3
import os
import sys

checks = [
    ("assets/sdroot/splash.raw", 153600),
    ("assets/sdroot/VERSION.TXT", None),
    ("assets/sdroot.zip", None),
]

ok = True
for path, expect_size in checks:
    if not os.path.exists(path):
        print(f"missing: {path}")
        ok = False
        continue
    if expect_size is not None:
        size = os.path.getsize(path)
        if size != expect_size:
            print(f"size mismatch: {path} expected={expect_size} got={size}")
            ok = False

if not ok:
    print("Asset verification failed.")
    print("Run:")
    print("  python3 tools/make_splash.py")
    print("  python3 tools/make_sd_image.py")
    sys.exit(1)

print("Assets verified")
