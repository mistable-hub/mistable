#include "scale.h"

#define SRC_W 320
#define SRC_H 240
#define DST_W 640

void scale_2x_line(uint16_t *line_buf, uint32_t y, const uint16_t *src) {
  if (!src) {
    for (uint32_t x = 0; x < DST_W; ++x) {
      line_buf[x] = 0;
    }
    return;
  }
  uint32_t src_y = y / 2;
  if (src_y >= SRC_H) {
    src_y = SRC_H - 1;
  }
  const uint16_t *row = src + (src_y * SRC_W);
  for (uint32_t x = 0; x < DST_W; ++x) {
    uint32_t src_x = x / 2;
    if (src_x >= SRC_W) {
      src_x = SRC_W - 1;
    }
    line_buf[x] = row[src_x];
  }
}
