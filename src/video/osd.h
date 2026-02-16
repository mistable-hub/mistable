#ifndef OSD_H
#define OSD_H

#include <stdbool.h>
#include <stdint.h>

void osd_draw_scanline(uint16_t y, uint16_t *linebuf, uint16_t width, bool enabled);

#endif
