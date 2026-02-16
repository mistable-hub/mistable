#include "osd.h"

static int g_osd_enabled;

void osd_set_enabled(int enabled) {
  g_osd_enabled = enabled;
}

int osd_get_enabled(void) {
  return g_osd_enabled;
}

void osd_compose_scanline(int y, uint16_t *line, int width) {
  if (!g_osd_enabled || y >= 64) {
    return;
  }
  int max = width < 160 ? width : 160;
  for (int x = 0; x < max; ++x) {
    if ((x % 2) == 0) {
      line[x] = 0xFFFF;
    }
  }
}
