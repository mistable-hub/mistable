#include "patterns.h"

uint16_t pattern_colorbars_pixel(uint16_t x, uint16_t y, uint32_t frame) {
  (void)y;
  uint16_t band = x / 80;
  uint16_t phase = (frame >> 4) & 1u;
  switch (band) {
    case 0: return phase ? 0xF800 : 0x001F;
    case 1: return 0xFFE0;
    case 2: return 0x07E0;
    case 3: return 0xFFFF;
    case 4: return 0xF81F;
    case 5: return 0x07FF;
    case 6: return 0x4208;
    default: return 0x0000;
  }
}
