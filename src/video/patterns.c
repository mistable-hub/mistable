#include "video/patterns.h"

static const uint16_t k_bars[8] = {
  0xffff, 0xffe0, 0x07ff, 0x07e0, 0xf81f, 0xf800, 0x001f, 0x0000
};

void patterns_render_colorbars(uint16_t y, uint16_t *line_out, uint16_t width, uint32_t frame_counter) {
  (void)y;
  for (uint16_t x = 0; x < width; ++x) {
    const uint16_t bar = (uint16_t)((x * 8u) / width);
    line_out[x] = k_bars[bar];
  }

  const uint16_t y0 = 16u;
  const uint16_t y1 = 24u;
  if (y >= y0 && y < y1) {
    for (uint16_t i = 0; i < 10u; ++i) {
      const uint16_t x = (uint16_t)(8u + i * 8u);
      if (x + 2u < width) {
        const uint8_t bit = (uint8_t)((frame_counter >> (9u - i)) & 1u);
        line_out[x] = bit ? 0xffff : 0x0000;
        line_out[x + 1u] = bit ? 0xffff : 0x0000;
      }
    }
  }
}
