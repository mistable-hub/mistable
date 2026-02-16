#include "patterns.h"

uint16_t pattern_colorbar_rgb565(int x, int y, uint32_t frame_counter) {
  (void)y;
  (void)frame_counter;
  int bar = x / 80;
  switch (bar) {
    case 0: return 0xF800;
    case 1: return 0xFFE0;
    case 2: return 0x07E0;
    case 3: return 0x07FF;
    case 4: return 0x001F;
    case 5: return 0xF81F;
    case 6: return 0xFFFF;
    default: return 0x0000;
  }
}
