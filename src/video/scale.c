#include "scale.h"

void scale_2x_rgb565(const uint16_t *src320x240, uint16_t *dst640x480) {
  for (int y = 0; y < 240; ++y) {
    for (int x = 0; x < 320; ++x) {
      uint16_t p = src320x240[y * 320 + x];
      int dx = x * 2;
      int dy = y * 2;
      dst640x480[dy * 640 + dx] = p;
      dst640x480[dy * 640 + dx + 1] = p;
      dst640x480[(dy + 1) * 640 + dx] = p;
      dst640x480[(dy + 1) * 640 + dx + 1] = p;
    }
  }
}
