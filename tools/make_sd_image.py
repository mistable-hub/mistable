#!/usr/bin/env python3
import os
import shutil
import subprocess
import zipfile

ROOT = "assets/sdroot"
ZIP_PATH = "assets/sdroot.zip"
IMG_PATH = "assets/sdcard.img"


def ensure_root():
    need = ["splash.raw", "VERSION.TXT"]
    missing = [n for n in need if not os.path.exists(os.path.join(ROOT, n))]
    if missing:
        raise SystemExit(
            "Missing files in assets/sdroot: " + ", ".join(missing) +
            "\nRun: python3 tools/make_splash.py"
        )


def make_zip():
    with zipfile.ZipFile(ZIP_PATH, "w", zipfile.ZIP_DEFLATED) as zf:
        zf.write(os.path.join(ROOT, "splash.raw"), "splash.raw")
        zf.write(os.path.join(ROOT, "VERSION.TXT"), "VERSION.TXT")
    print(f"Created {ZIP_PATH}")


def have_mtools():
    return shutil.which("mformat") is not None and shutil.which("mcopy") is not None


def make_img_mtools():
    size_mb = 16
    with open(IMG_PATH, "wb") as f:
        f.truncate(size_mb * 1024 * 1024)
    subprocess.check_call(["mformat", "-i", IMG_PATH, "-F", "::"])
    subprocess.check_call(["mcopy", "-i", IMG_PATH, os.path.join(ROOT, "splash.raw"), "::/splash.raw"])
    subprocess.check_call(["mcopy", "-i", IMG_PATH, os.path.join(ROOT, "VERSION.TXT"), "::/VERSION.TXT"])
    print(f"Created {IMG_PATH} with mtools")


def main():
    ensure_root()
    make_zip()

    if have_mtools():
        try:
            make_img_mtools()
        except subprocess.CalledProcessError as exc:
            print(f"mtools failed: {exc}")
            print("Fallback: use assets/sdroot.zip and copy files manually to FAT SD root")
    else:
        print("mtools not found; skipping sdcard.img")
        print("Install suggestion (Ubuntu): sudo apt-get install mtools")
        print("Fallback: copy assets/sdroot/* to FAT SD root")


if __name__ == "__main__":
    main()
