#!/usr/bin/env python3
import os
import shutil
import subprocess
import zipfile

ROOT = "assets/sdroot"
ZIP_OUT = "assets/sdroot.zip"
IMG_OUT = "assets/sdcard.img"


def ensure_root_files():
    if not os.path.exists(os.path.join(ROOT, "splash.raw")):
        raise SystemExit("Missing assets/sdroot/splash.raw. Run: python3 tools/make_splash.py")
    if not os.path.exists(os.path.join(ROOT, "VERSION.TXT")):
        raise SystemExit("Missing assets/sdroot/VERSION.TXT")


def make_zip():
    with zipfile.ZipFile(ZIP_OUT, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        zf.write(os.path.join(ROOT, "splash.raw"), arcname="splash.raw")
        zf.write(os.path.join(ROOT, "VERSION.TXT"), arcname="VERSION.TXT")
    print(f"Created {ZIP_OUT}")


def have_mtools():
    return shutil.which("mformat") and shutil.which("mcopy")


def make_img_with_mtools():
    if os.path.exists(IMG_OUT):
        os.remove(IMG_OUT)
    subprocess.check_call(["mformat", "-i", IMG_OUT, "-f", "1440", "::"])
    subprocess.check_call(["mcopy", "-i", IMG_OUT, os.path.join(ROOT, "splash.raw"), "::/"])
    subprocess.check_call(["mcopy", "-i", IMG_OUT, os.path.join(ROOT, "VERSION.TXT"), "::/"])
    print(f"Created {IMG_OUT} using mtools")


def main():
    ensure_root_files()
    make_zip()
    if have_mtools():
        try:
            make_img_with_mtools()
        except subprocess.CalledProcessError as e:
            print(f"mtools failed ({e}); continuing with {ZIP_OUT} only")
    else:
        print("mtools not found; generated sdroot.zip only")
        print("Install mtools (Debian/Ubuntu): sudo apt-get install mtools")
    print("Copy files from assets/sdroot/ to FAT SD root, or use sdcard.img when available.")


if __name__ == "__main__":
    main()
