#include "osd.h"

#include "font8x8.h"

#include <stdio.h>
#include <string.h>

static void draw_text(uint16_t *scanline, int y, int x0, const char *text, uint16_t fg) {
  for (int i = 0; text[i] != '\0'; ++i) {
    const uint8_t *g = font8x8_get(text[i]);
    int gy = y % 8;
    uint8_t row = g[gy];
    int x = x0 + i * 8;
    for (int bit = 0; bit < 8; ++bit) {
      if ((row >> (7 - bit)) & 1u) {
        int px = x + bit;
        if (px >= 0 && px < 640) {
          scanline[px] = fg;
        }
      }
    }
  }
}

void osd_compose_scanline(uint16_t *scanline, int y, const shared_status_t *status, int enabled) {
  if (!enabled) {
    return;
  }

  if (y < 40) {
    for (int i = 0; i < 220; ++i) {
      scanline[i] = 0x0000;
    }
  }

  if (y >= 0 && y < 8) {
    draw_text(scanline, y, 0, "mistable OSD", 0xFFFF);
  } else if (y >= 10 && y < 18) {
    draw_text(scanline, y - 10, 0, status->sd_state == SD_STATE_SPLASH_OK ? "SD: MOUNTED" : "SD: NO", 0xFFE0);
  } else if (y >= 20 && y < 28) {
    draw_text(scanline, y - 20, 0, status->kb_state == KB_STATE_CONNECTED ? "KB: OK" : "KB: NO", 0xFFE0);
  } else if (y >= 30 && y < 38) {
    char up[32];
    memset(up, 0, sizeof(up));
    (void)snprintf(up, sizeof(up), "UP: %lu", (unsigned long)status->uptime_seconds);
    draw_text(scanline, y - 30, 0, up, 0xFFE0);
  }
}
