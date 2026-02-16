#include "patterns.h"

#define WIDTH 640

static uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
  return (uint16_t)(((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

void pattern_colorbars_line(uint16_t *line_buf, uint32_t y) {
  (void)y;
  const uint16_t colors[8] = {
    rgb565(255, 255, 255),
    rgb565(255, 255, 0),
    rgb565(0, 255, 255),
    rgb565(0, 255, 0),
    rgb565(255, 0, 255),
    rgb565(255, 0, 0),
    rgb565(0, 0, 255),
    rgb565(0, 0, 0)
  };
  for (uint32_t x = 0; x < WIDTH; ++x) {
    uint32_t bar = (x * 8) / WIDTH;
    line_buf[x] = colors[bar];
  }
}
