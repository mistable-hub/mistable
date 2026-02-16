#include "scale.h"

uint16_t scale2x_sample_rgb565(const uint16_t *src, int src_w, int src_h, int x, int y) {
  int sx = x / 2;
  int sy = y / 2;
  if (sx < 0 || sx >= src_w || sy < 0 || sy >= src_h) {
    return 0;
  }
  return src[sy * src_w + sx];
}
