#!/usr/bin/env python3
import os

OUT = "assets/sdroot/splash.raw"
W = 320
H = 240

FONT = {
    " ": [0,0,0,0,0,0,0],
    "A": [0x0E,0x11,0x11,0x1F,0x11,0x11,0x11],
    "B": [0x1E,0x11,0x11,0x1E,0x11,0x11,0x1E],
    "E": [0x1F,0x10,0x10,0x1E,0x10,0x10,0x1F],
    "H": [0x11,0x11,0x11,0x1F,0x11,0x11,0x11],
    "I": [0x1F,0x04,0x04,0x04,0x04,0x04,0x1F],
    "L": [0x10,0x10,0x10,0x10,0x10,0x10,0x1F],
    "M": [0x11,0x1B,0x15,0x15,0x11,0x11,0x11],
    "P": [0x1E,0x11,0x11,0x1E,0x10,0x10,0x10],
    "1": [0x04,0x0C,0x04,0x04,0x04,0x04,0x0E],
    "S": [0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E],
    "T": [0x1F,0x04,0x04,0x04,0x04,0x04,0x04],
}


def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def put_text(buf, x0, y0, text, color):
    for i, ch in enumerate(text):
        glyph = FONT.get(ch, FONT[" "])
        for y, row in enumerate(glyph):
            yy = y0 + y
            if yy < 0 or yy >= H:
                continue
            for x in range(5):
                if row & (1 << (4 - x)):
                    xx = x0 + i * 6 + x
                    if 0 <= xx < W:
                        buf[yy * W + xx] = color


def main():
    os.makedirs("assets/sdroot", exist_ok=True)
    pixels = [0] * (W * H)
    for y in range(H):
        for x in range(W):
            r = (x * 255) // (W - 1)
            g = (y * 255) // (H - 1)
            b = ((x ^ y) * 255) // 255
            if ((x // 16) + (y // 16)) & 1:
                r //= 2
                g //= 2
            pixels[y * W + x] = rgb565(r, g, b)

    put_text(pixels, 72, 116, "MISTABLE PHASE1", rgb565(255, 255, 255))

    with open(OUT, "wb") as f:
        for px in pixels:
            f.write(bytes((px & 0xFF, (px >> 8) & 0xFF)))

    size = os.path.getsize(OUT)
    if size != 153600:
        raise SystemExit(f"invalid splash size: {size}")
    print(f"generated {OUT} ({size} bytes)")


if __name__ == "__main__":
    main()
