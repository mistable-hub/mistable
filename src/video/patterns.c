#include "patterns.h"

void patterns_init(void) {
}

uint16_t patterns_colorbar_pixel(uint16_t x, uint16_t y) {
  static const uint16_t bars[8] = {
    0xF800, 0x07E0, 0x001F, 0xFFE0, 0xF81F, 0x07FF, 0xFFFF, 0x0000
  };
  (void)y;
  return bars[(x / 80u) & 7u];
}
