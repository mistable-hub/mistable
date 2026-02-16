#include "video/osd.h"

#include <stdio.h>
#include <string.h>

#include "video/font8x8.h"

static void draw_text(uint16_t y, uint16_t *line, uint16_t width, uint16_t x0, uint16_t y0, const char *text) {
  if (y < y0 || y >= (uint16_t)(y0 + 8u)) {
    return;
  }

  const uint8_t gy = (uint8_t)(y - y0);
  for (size_t i = 0; text[i] != '\0'; ++i) {
    const uint16_t gx0 = (uint16_t)(x0 + (uint16_t)(i * 8u));
    for (uint8_t gx = 0; gx < 8u; ++gx) {
      const uint16_t px = (uint16_t)(gx0 + gx);
      if (px >= width) {
        continue;
      }
      if (font8x8_get_pixel(text[i], gx, gy)) {
        line[px] = 0xffff;
      }
    }
  }
}

void osd_compose_scanline(uint16_t y, uint16_t *line, uint16_t width, const system_status_t *status, uint32_t frame_counter, bool enabled) {
  (void)frame_counter;
  if (!enabled || status == 0) {
    return;
  }

  char sd_line[32];
  char kb_line[32];
  char up_line[32];

  snprintf(sd_line, sizeof(sd_line), "SD: %s", status->sd_state == SD_STATE_SPLASH_OK || status->sd_state == SD_STATE_MOUNTED ? "MOUNTED" : "NO");
  snprintf(kb_line, sizeof(kb_line), "KB: %s", status->kb_state == KB_STATE_CONNECTED ? "OK" : "NO");
  snprintf(up_line, sizeof(up_line), "UP: %lu", (unsigned long)status->uptime_seconds);

  draw_text(y, line, width, 8u, 8u, "MISTABLE OSD");
  draw_text(y, line, width, 8u, 20u, sd_line);
  draw_text(y, line, width, 8u, 32u, kb_line);
  draw_text(y, line, width, 8u, 44u, up_line);
}
