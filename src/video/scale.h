#ifndef SCALE_H
#define SCALE_H

#include <stdint.h>

void scale_2x_scanline_rgb565(const uint16_t *src, uint16_t src_w, uint16_t *dst);

#endif
