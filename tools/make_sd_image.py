#!/usr/bin/env python3
import pathlib
import shutil
import subprocess
import tempfile
import zipfile

ROOT = pathlib.Path("assets/sdroot")
SPLASH = ROOT / "splash.raw"
VERSION = ROOT / "VERSION.TXT"
ZIP_OUT = pathlib.Path("assets/sdroot.zip")
IMG_OUT = pathlib.Path("assets/sdcard.img")


def ensure_assets() -> None:
    ROOT.mkdir(parents=True, exist_ok=True)
    if not VERSION.exists():
        VERSION.write_text("mistable phase1\n", encoding="ascii")
    if not SPLASH.exists() or SPLASH.stat().st_size != 153600:
        subprocess.check_call(["python3", "tools/make_splash.py"])


def make_zip() -> None:
    with zipfile.ZipFile(ZIP_OUT, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        zf.write(SPLASH, arcname="splash.raw")
        zf.write(VERSION, arcname="VERSION.TXT")
    print(f"created {ZIP_OUT}")


def have_mtools() -> bool:
    return shutil.which("mformat") is not None and shutil.which("mcopy") is not None


def make_img() -> bool:
    if not have_mtools():
        print("mtools not available; skipped assets/sdcard.img")
        return False

    with tempfile.TemporaryDirectory() as td:
        cfg = pathlib.Path(td) / "mtoolsrc"
        cfg.write_text(f"drive z: file=\"{IMG_OUT}\" partition=0\n", encoding="ascii")
        with open(IMG_OUT, "wb") as fp:
            fp.truncate(64 * 1024 * 1024)

        env = dict(**__import__("os").environ)
        env["MTOOLSRC"] = str(cfg)
        subprocess.check_call(["mformat", "-F", "z:"], env=env)
        subprocess.check_call(["mcopy", "-o", str(SPLASH), "z::/splash.raw"], env=env)
        subprocess.check_call(["mcopy", "-o", str(VERSION), "z::/VERSION.TXT"], env=env)
    print(f"created {IMG_OUT}")
    return True


def main() -> None:
    ensure_assets()
    make_zip()
    if make_img():
        print("Use assets/sdcard.img directly, or copy assets/sdroot/* to FAT SD root.")
    else:
        print("Copy assets/sdroot/* to the SD FAT root manually.")
        print("Install mtools (Ubuntu: sudo apt-get install mtools) to enable sdcard.img generation.")


if __name__ == "__main__":
    main()
