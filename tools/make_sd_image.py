#!/usr/bin/env python3
import os
import shutil
import subprocess
import zipfile

SDROOT = "assets/sdroot"
ZIP_OUT = "assets/sdroot.zip"
IMG_OUT = "assets/sdcard.img"


def ensure_inputs():
    required = [
        os.path.join(SDROOT, "splash.raw"),
        os.path.join(SDROOT, "VERSION.TXT"),
    ]
    missing = [p for p in required if not os.path.isfile(p)]
    if missing:
        for p in missing:
            print(f"ERROR: missing {p}")
        print("Run: python3 tools/make_splash.py")
        raise SystemExit(1)


def make_zip():
    with zipfile.ZipFile(ZIP_OUT, "w", zipfile.ZIP_DEFLATED) as zf:
        zf.write(os.path.join(SDROOT, "splash.raw"), "splash.raw")
        zf.write(os.path.join(SDROOT, "VERSION.TXT"), "VERSION.TXT")
    print(f"OK: wrote {ZIP_OUT}")


def have_mtools():
    return shutil.which("mformat") is not None and shutil.which("mcopy") is not None


def make_img_if_possible():
    if not have_mtools():
        print("INFO: mtools not found; skipping assets/sdcard.img")
        print("Install on Debian/Ubuntu: sudo apt-get install -y mtools")
        print("Manual fallback: copy assets/sdroot/* onto a FAT32 SD card root")
        return

    with open(IMG_OUT, "wb") as f:
        f.truncate(16 * 1024 * 1024)

    subprocess.run(["mformat", "-i", IMG_OUT, "::"], check=True)
    subprocess.run(["mcopy", "-i", IMG_OUT, os.path.join(SDROOT, "splash.raw"), "::splash.raw"], check=True)
    subprocess.run(["mcopy", "-i", IMG_OUT, os.path.join(SDROOT, "VERSION.TXT"), "::VERSION.TXT"], check=True)
    print(f"OK: wrote {IMG_OUT}")


def main():
    os.makedirs("assets", exist_ok=True)
    ensure_inputs()
    make_zip()
    make_img_if_possible()
    print("Done. Use assets/sdroot.zip or copy assets/sdroot/* to SD root.")


if __name__ == "__main__":
    main()
