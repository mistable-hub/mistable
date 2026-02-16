#ifndef OSD_H
#define OSD_H

#include <stdint.h>

#include "status.h"

void osd_compose_scanline(uint16_t *scanline, int y, const shared_status_t *status, int enabled);

#endif
