#!/usr/bin/env python3
import os
import shutil
import subprocess
import zipfile

ROOT = os.path.join('assets', 'sdroot')
ZIP_PATH = os.path.join('assets', 'sdroot.zip')
IMG_PATH = os.path.join('assets', 'sdcard.img')


def ensure_root():
    os.makedirs(ROOT, exist_ok=True)
    splash = os.path.join(ROOT, 'splash.raw')
    version = os.path.join(ROOT, 'VERSION.TXT')
    if not os.path.exists(splash):
        raise SystemExit('ERROR: assets/sdroot/splash.raw missing. Run tools/make_splash.py')
    if not os.path.exists(version):
        raise SystemExit('ERROR: assets/sdroot/VERSION.TXT missing.')


def make_zip():
    with zipfile.ZipFile(ZIP_PATH, 'w', compression=zipfile.ZIP_DEFLATED) as zf:
        for name in ['splash.raw', 'VERSION.TXT']:
            zf.write(os.path.join(ROOT, name), arcname=name)
    print(f"Wrote {ZIP_PATH}")


def have_mtools():
    return shutil.which('mformat') and shutil.which('mcopy')


def make_img():
    if os.path.exists(IMG_PATH):
        os.remove(IMG_PATH)
    size_mb = 16
    with open(IMG_PATH, 'wb') as f:
        f.truncate(size_mb * 1024 * 1024)

    subprocess.check_call(['mformat', '-i', IMG_PATH, '-F', '::'])
    subprocess.check_call(['mcopy', '-i', IMG_PATH, os.path.join(ROOT, 'splash.raw'), '::/splash.raw'])
    subprocess.check_call(['mcopy', '-i', IMG_PATH, os.path.join(ROOT, 'VERSION.TXT'), '::/VERSION.TXT'])
    print(f"Wrote {IMG_PATH}")


def main():
    ensure_root()
    make_zip()
    if have_mtools():
        make_img()
    else:
        print('mtools not found; skipping sdcard.img.')
        print('Install with: sudo apt-get install mtools')


if __name__ == '__main__':
    main()
