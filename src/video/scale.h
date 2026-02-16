#ifndef SCALE_H
#define SCALE_H

#include <stdint.h>

uint16_t scale2x_sample_rgb565(const uint16_t *src, int src_w, int src_h, int x, int y);

#endif
