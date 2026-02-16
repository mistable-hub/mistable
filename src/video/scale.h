#ifndef SCALE_H
#define SCALE_H

#include <stdint.h>

void scale_2x_rgb565(const uint16_t *src320x240, uint16_t *dst640x480);

#endif
