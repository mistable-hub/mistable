#ifndef OSD_H
#define OSD_H

#include <stdbool.h>
#include <stdint.h>

#include "status.h"

void osd_compose_scanline(uint16_t y, uint16_t *line, uint16_t width, const system_status_t *status, uint32_t frame_counter, bool enabled);

#endif
