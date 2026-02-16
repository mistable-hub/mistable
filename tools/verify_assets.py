#!/usr/bin/env python3
import os
import sys

SPLASH = os.path.join('assets', 'sdroot', 'splash.raw')
VERSION = os.path.join('assets', 'sdroot', 'VERSION.TXT')
ZIP = os.path.join('assets', 'sdroot.zip')


def main():
    ok = True
    if not os.path.exists(SPLASH):
        print('Missing assets/sdroot/splash.raw. Run tools/make_splash.py')
        ok = False
    else:
        size = os.path.getsize(SPLASH)
        if size != 153600:
            print(f'Invalid splash.raw size: {size} bytes')
            ok = False
    if not os.path.exists(VERSION):
        print('Missing assets/sdroot/VERSION.TXT')
        ok = False
    if not os.path.exists(ZIP):
        print('Missing assets/sdroot.zip. Run tools/make_sd_image.py')
        ok = False
    if not ok:
        sys.exit(1)
    print('Assets verified.')


if __name__ == '__main__':
    main()
