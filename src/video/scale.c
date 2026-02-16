#include "scale.h"

void scale_2x_scanline_rgb565(const uint16_t *src, uint16_t src_w, uint16_t *dst) {
  for (uint16_t i = 0; i < src_w; ++i) {
    uint16_t p = src[i];
    dst[i * 2u] = p;
    dst[i * 2u + 1u] = p;
  }
}
