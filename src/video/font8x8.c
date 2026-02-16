#include "font8x8.h"

static const uint8_t glyph_space[8] = {0,0,0,0,0,0,0,0};
static const uint8_t glyph_block[8] = {0x7e,0x42,0x42,0x42,0x42,0x42,0x7e,0x00};

const uint8_t *font8x8_get(char c) {
  if (c == ' ') {
    return glyph_space;
  }
  return glyph_block;
}
