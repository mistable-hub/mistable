#!/usr/bin/env python3
import os

W = 320
H = 240
OUT = "assets/sdroot/splash.raw"
TEXT = "MISTABLE PHASE1"

FONT = {
    "M": [0b10001,0b11011,0b10101,0b10001,0b10001],
    "I": [0b11111,0b00100,0b00100,0b00100,0b11111],
    "S": [0b11111,0b10000,0b11111,0b00001,0b11111],
    "T": [0b11111,0b00100,0b00100,0b00100,0b00100],
    "A": [0b01110,0b10001,0b11111,0b10001,0b10001],
    "B": [0b11110,0b10001,0b11110,0b10001,0b11110],
    "L": [0b10000,0b10000,0b10000,0b10000,0b11111],
    "E": [0b11111,0b10000,0b11110,0b10000,0b11111],
    "P": [0b11110,0b10001,0b11110,0b10000,0b10000],
    "H": [0b10001,0b10001,0b11111,0b10001,0b10001],
    "1": [0b00100,0b01100,0b00100,0b00100,0b01110],
    " ": [0,0,0,0,0],
}


def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def put_text(pix):
    scale = 4
    cw, ch = 5, 5
    total_w = len(TEXT) * (cw + 1) * scale
    ox = (W - total_w) // 2
    oy = (H - ch * scale) // 2
    fg = rgb565(255, 255, 255)
    for i, c in enumerate(TEXT):
        glyph = FONT.get(c, FONT[" "])
        for gy, row in enumerate(glyph):
            for gx in range(cw):
                if (row >> (cw - 1 - gx)) & 1:
                    for sy in range(scale):
                        for sx in range(scale):
                            x = ox + i * (cw + 1) * scale + gx * scale + sx
                            y = oy + gy * scale + sy
                            if 0 <= x < W and 0 <= y < H:
                                pix[y * W + x] = fg


def main():
    os.makedirs("assets/sdroot", exist_ok=True)
    pix = [0] * (W * H)
    for y in range(H):
        for x in range(W):
            r = (x * 255) // (W - 1)
            g = (y * 255) // (H - 1)
            b = ((x ^ y) & 0xFF)
            pix[y * W + x] = rgb565(r, g, b)
    put_text(pix)
    with open(OUT, "wb") as f:
        for p in pix:
            f.write(bytes((p & 0xFF, (p >> 8) & 0xFF)))
    size = os.path.getsize(OUT)
    if size != 153600:
        raise SystemExit(f"ERROR: expected 153600 bytes, got {size}")
    print(f"Wrote {OUT} ({size} bytes)")


if __name__ == "__main__":
    main()
