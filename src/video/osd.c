#include "osd.h"

void osd_draw_scanline(uint16_t y, uint16_t *linebuf, uint16_t width, bool enabled) {
  if (!enabled || y >= 48) {
    return;
  }
  for (uint16_t x = 0; x < width && x < 200; ++x) {
    if (x == 0 || y == 0 || x == 199 || y == 47) {
      linebuf[x] = 0xFFFF;
    }
  }
}
