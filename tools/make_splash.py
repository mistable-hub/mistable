#!/usr/bin/env python3
import os

W = 320
H = 240

FONT = {
    ' ': ["00000"] * 7,
    'A': ["01110","10001","10001","11111","10001","10001","10001"],
    'B': ["11110","10001","11110","10001","10001","10001","11110"],
    'E': ["11111","10000","10000","11110","10000","10000","11111"],
    'H': ["10001","10001","10001","11111","10001","10001","10001"],
    'I': ["11111","00100","00100","00100","00100","00100","11111"],
    'L': ["10000","10000","10000","10000","10000","10000","11111"],
    'M': ["10001","11011","10101","10001","10001","10001","10001"],
    'P': ["11110","10001","10001","11110","10000","10000","10000"],
    'S': ["01111","10000","10000","01110","00001","00001","11110"],
    'T': ["11111","00100","00100","00100","00100","00100","00100"],
    '1': ["00100","01100","00100","00100","00100","00100","01110"],
}


def rgb565(r, g, b):
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


def draw_text(pixels, text, x, y):
    for idx, ch in enumerate(text):
        glyph = FONT.get(ch, FONT[' '])
        for gy, row in enumerate(glyph):
            for gx, bit in enumerate(row):
                if bit == '1':
                    px = x + idx * 6 + gx
                    py = y + gy
                    if 0 <= px < W and 0 <= py < H:
                        pixels[py][px] = rgb565(255, 255, 255)


def main():
    out_dir = os.path.join('assets', 'sdroot')
    os.makedirs(out_dir, exist_ok=True)
    pixels = [[0 for _ in range(W)] for _ in range(H)]

    for y in range(H):
        for x in range(W):
            r = (x * 255) // (W - 1)
            g = (y * 255) // (H - 1)
            b = ((x + y) * 255) // (W + H - 2)
            pixels[y][x] = rgb565(r, g, b)

    text = "MISTABLE PHASE1"
    text_w = len(text) * 6
    start_x = (W - text_w) // 2
    start_y = (H - 7) // 2
    draw_text(pixels, text, start_x, start_y)

    out_path = os.path.join(out_dir, 'splash.raw')
    with open(out_path, 'wb') as f:
        for y in range(H):
            for x in range(W):
                val = pixels[y][x]
                f.write(val.to_bytes(2, byteorder='little'))

    expected = W * H * 2
    actual = os.path.getsize(out_path)
    if actual != expected:
        raise SystemExit(f"splash.raw size incorrect: {actual} != {expected}")
    print(f"Wrote {out_path} ({actual} bytes)")


if __name__ == '__main__':
    main()
