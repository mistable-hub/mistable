#include "video/scale.h"

static const uint16_t *g_splash_pixels;
static bool g_splash_valid;

void scale_set_splash(const uint16_t *pixels, bool valid) {
  g_splash_pixels = pixels;
  g_splash_valid = valid;
}

bool scale_has_splash(void) {
  return g_splash_valid && g_splash_pixels != 0;
}

void scale_render_2x(uint16_t y, uint16_t *line_out, uint16_t width) {
  if (!scale_has_splash()) {
    for (uint16_t x = 0; x < width; ++x) {
      line_out[x] = 0;
    }
    return;
  }

  const uint16_t sy = (uint16_t)(y / 2u);
  for (uint16_t x = 0; x < width; ++x) {
    const uint16_t sx = (uint16_t)(x / 2u);
    const uint32_t idx = (uint32_t)sy * 320u + (uint32_t)sx;
    line_out[x] = g_splash_pixels[idx];
  }
}
