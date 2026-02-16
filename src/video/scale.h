#ifndef SCALE_H
#define SCALE_H

#include <stdint.h>

void scale_2x_line(uint16_t *line_buf, uint32_t y, const uint16_t *src);

#endif
