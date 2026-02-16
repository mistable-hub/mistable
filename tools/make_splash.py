#!/usr/bin/env python3
import os

W = 320
H = 240
OUT = "assets/sdroot/splash.raw"

FONT5X7 = {
    'A':[0x0E,0x11,0x11,0x1F,0x11,0x11,0x11],
    'B':[0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E],
    'E':[0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F],
    'H':[0x11,0x11,0x11,0x1F,0x11,0x11,0x11],
    'I':[0x1F,0x04,0x04,0x04,0x04,0x04,0x1F],
    'L':[0x10,0x10,0x10,0x10,0x10,0x10,0x1F],
    'M':[0x11,0x1B,0x15,0x15,0x11,0x11,0x11],
    'P':[0x1E,0x11,0x11,0x1E,0x10,0x10,0x10],
    'S':[0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E],
    'T':[0x1F,0x04,0x04,0x04,0x04,0x04,0x04],
    '1':[0x04,0x0C,0x04,0x04,0x04,0x04,0x0E],
    ' ': [0x00,0x00,0x00,0x00,0x00,0x00,0x00],
}

def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def putpix(buf, x, y, color):
    if 0 <= x < W and 0 <= y < H:
        buf[y * W + x] = color


def draw_text(buf, x0, y0, text, color):
    x = x0
    for ch in text:
        glyph = FONT5X7.get(ch, FONT5X7[' '])
        for gy, row in enumerate(glyph):
            for gx in range(5):
                if row & (1 << (4 - gx)):
                    putpix(buf, x + gx, y0 + gy, color)
        x += 6


def main():
    os.makedirs("assets/sdroot", exist_ok=True)
    fb = [0] * (W * H)
    for y in range(H):
        for x in range(W):
            r = (x * 255) // (W - 1)
            g = (y * 255) // (H - 1)
            b = ((x + y) * 255) // (W + H - 2)
            fb[y * W + x] = rgb565(r, g, b)

    draw_text(fb, 70, 110, "MISTABLE PHASE1", rgb565(255, 255, 255))

    with open(OUT, "wb") as f:
        for pix in fb:
            f.write(bytes((pix & 0xFF, (pix >> 8) & 0xFF)))

    size = os.path.getsize(OUT)
    if size != 153600:
        raise SystemExit(f"ERROR: {OUT} wrong size {size}, expected 153600")
    print(f"OK: wrote {OUT} ({size} bytes)")


if __name__ == "__main__":
    main()
