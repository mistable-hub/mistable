#include "osd.h"
#include "font8x8.h"
#include "status.h"
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 640
#define OSD_X 8
#define OSD_Y 8
#define CHAR_W 8
#define CHAR_H 8
#define LINE_COUNT 4

static uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

static void draw_char(uint16_t *line_buf, uint32_t y, uint32_t x, char c) {
  const uint8_t *glyph = font8x8_get(c);
  uint32_t row = y % CHAR_H;
  uint8_t bits = glyph[row];
  for (uint32_t col = 0; col < CHAR_W; ++col) {
    if (bits & (1u << (7 - col))) {
      uint32_t px = x + col;
      if (px < WIDTH) {
        line_buf[px] = rgb565(255, 255, 255);
      }
    }
  }
}

static void draw_text(uint16_t *line_buf, uint32_t y, uint32_t x, const char *text) {
  uint32_t cursor = x;
  while (*text) {
    draw_char(line_buf, y, cursor, *text);
    cursor += CHAR_W;
    text++;
  }
}

void osd_render_line(uint16_t *line_buf, uint32_t y) {
  if (y < OSD_Y || y >= OSD_Y + (LINE_COUNT * CHAR_H)) {
    return;
  }

  uint32_t line_index = (y - OSD_Y) / CHAR_H;
  status_t st = status_get();
  char buf[32];

  switch (line_index) {
    case 0:
      draw_text(line_buf, y, OSD_X, "mistable OSD");
      break;
    case 1:
      if (st.sd_state == SD_STATE_SPLASH_OK || st.sd_state == SD_STATE_MOUNTED) {
        draw_text(line_buf, y, OSD_X, "SD: MOUNTED");
      } else {
        draw_text(line_buf, y, OSD_X, "SD: NO");
      }
      break;
    case 2:
      if (st.kb_state == KB_STATE_CONNECTED) {
        draw_text(line_buf, y, OSD_X, "KB: OK");
      } else {
        draw_text(line_buf, y, OSD_X, "KB: NO");
      }
      break;
    case 3:
      snprintf(buf, sizeof(buf), "UP: %lu", (unsigned long)st.uptime_seconds);
      draw_text(line_buf, y, OSD_X, buf);
      break;
    default:
      break;
  }
}
