#!/usr/bin/env python3
import pathlib
import sys

checks = [
    (pathlib.Path("assets/sdroot/splash.raw"), 153600),
    (pathlib.Path("assets/sdroot/VERSION.TXT"), None),
    (pathlib.Path("assets/sdroot.zip"), None),
]

ok = True
for path, size in checks:
    if not path.exists():
        print(f"ERROR: missing {path}")
        ok = False
        continue
    if size is not None and path.stat().st_size != size:
        print(f"ERROR: {path} size {path.stat().st_size} != {size}")
        ok = False

if not ok:
    print("Run: python3 tools/make_splash.py && python3 tools/make_sd_image.py")
    sys.exit(1)

print("assets verified")
