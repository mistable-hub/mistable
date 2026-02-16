#!/usr/bin/env python3
import os
import shutil
import subprocess
import zipfile

ROOT = "assets/sdroot"
ZIP = "assets/sdroot.zip"
IMG = "assets/sdcard.img"


def run(cmd):
    return subprocess.run(cmd, check=False, text=True, capture_output=True)


def ensure_root_files():
    req = ["splash.raw", "VERSION.TXT"]
    missing = [f for f in req if not os.path.exists(os.path.join(ROOT, f))]
    if missing:
        raise SystemExit("Missing in assets/sdroot: " + ", ".join(missing))


def make_zip():
    with zipfile.ZipFile(ZIP, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        for name in ["splash.raw", "VERSION.TXT"]:
            zf.write(os.path.join(ROOT, name), arcname=name)
    print(f"Created {ZIP}")


def make_img_if_mtools():
    if shutil.which("mformat") is None or shutil.which("mcopy") is None:
        print("mtools not found; skipping assets/sdcard.img")
        print("Install with: sudo apt-get install mtools")
        return
    size_mb = 64
    with open(IMG, "wb") as f:
        f.truncate(size_mb * 1024 * 1024)
    r = run(["mformat", "-i", IMG, "::"])
    if r.returncode != 0:
        print(r.stderr.strip())
        raise SystemExit("mformat failed")
    for name in ["splash.raw", "VERSION.TXT"]:
        r = run(["mcopy", "-i", IMG, os.path.join(ROOT, name), f"::{name}"])
        if r.returncode != 0:
            print(r.stderr.strip())
            raise SystemExit("mcopy failed")
    print(f"Created {IMG} (FAT image)")


def main():
    ensure_root_files()
    make_zip()
    make_img_if_mtools()
    print("Use assets/sdroot.zip contents to copy onto FAT SD card root.")


if __name__ == "__main__":
    main()
