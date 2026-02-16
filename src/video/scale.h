#ifndef SCALE_H
#define SCALE_H

#include <stdbool.h>
#include <stdint.h>

void scale_set_splash(const uint16_t *pixels, bool valid);
void scale_render_2x(uint16_t y, uint16_t *line_out, uint16_t width);
bool scale_has_splash(void);

#endif
