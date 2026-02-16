#ifndef OSD_H
#define OSD_H

#include <stdint.h>

void osd_set_enabled(int enabled);
int osd_get_enabled(void);
void osd_compose_scanline(int y, uint16_t *line, int width);

#endif
