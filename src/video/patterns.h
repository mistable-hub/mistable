#ifndef PATTERNS_H
#define PATTERNS_H

#include <stdint.h>

void patterns_init(void);
uint16_t patterns_colorbar_pixel(int x, int y, uint32_t frame_counter);

#endif
