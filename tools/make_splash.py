#!/usr/bin/env python3
import pathlib

WIDTH = 320
HEIGHT = 240
OUT = pathlib.Path("assets/sdroot/splash.raw")

GLYPHS = {
    "A": [0x1E, 0x05, 0x05, 0x1E, 0x00],
    "B": [0x1F, 0x15, 0x15, 0x0A, 0x00],
    "E": [0x1F, 0x15, 0x15, 0x11, 0x00],
    "H": [0x1F, 0x04, 0x04, 0x1F, 0x00],
    "I": [0x11, 0x1F, 0x11, 0x00, 0x00],
    "L": [0x1F, 0x10, 0x10, 0x10, 0x00],
    "M": [0x1F, 0x02, 0x04, 0x02, 0x1F],
    "P": [0x1F, 0x05, 0x05, 0x02, 0x00],
    "S": [0x12, 0x15, 0x15, 0x09, 0x00],
    "T": [0x01, 0x1F, 0x01, 0x00, 0x00],
    "1": [0x00, 0x12, 0x1F, 0x10, 0x00],
    " ": [0x00, 0x00, 0x00, 0x00, 0x00],
}


def rgb565(r: int, g: int, b: int) -> int:
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def draw_text(pix, text: str, x0: int, y0: int, color: int) -> None:
    for idx, ch in enumerate(text):
        glyph = GLYPHS.get(ch, GLYPHS[" "])
        gx0 = x0 + idx * 6
        for gx, col in enumerate(glyph):
            for gy in range(7):
                if (col >> gy) & 1:
                    x = gx0 + gx
                    y = y0 + gy
                    if 0 <= x < WIDTH and 0 <= y < HEIGHT:
                        pix[y * WIDTH + x] = color


def main() -> None:
    OUT.parent.mkdir(parents=True, exist_ok=True)
    pix = [0] * (WIDTH * HEIGHT)

    for y in range(HEIGHT):
        for x in range(WIDTH):
            r = (x * 255) // (WIDTH - 1)
            g = (y * 255) // (HEIGHT - 1)
            b = ((x ^ y) * 255) // 255
            pix[y * WIDTH + x] = rgb565(r, g, b)

    draw_text(pix, "MISTABLE PHASE1", 76, 110, rgb565(255, 255, 255))

    data = bytearray()
    for p in pix:
        data.append(p & 0xFF)
        data.append((p >> 8) & 0xFF)

    OUT.write_bytes(data)
    print(f"wrote {OUT} ({len(data)} bytes)")


if __name__ == "__main__":
    main()
