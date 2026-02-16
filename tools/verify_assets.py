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
        print(f"MISSING: {path}")
        ok = False
        continue
    if size is not None:
        got = os.path.getsize(path)
        if got != size:
            print(f"BAD SIZE: {path} expected {size} got {got}")
            ok = False
        else:
            print(f"OK: {path} size={got}")
    else:
        print(f"OK: {path}")

if not ok:
    print("Asset verification failed. Run:")
    print("  python3 tools/make_splash.py")
    print("  python3 tools/make_sd_image.py")
    sys.exit(1)

print("Asset verification PASSED")
