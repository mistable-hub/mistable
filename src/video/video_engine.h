#ifndef VIDEO_ENGINE_H
#define VIDEO_ENGINE_H

#include <stdint.h>

enum {
  SOURCE_TESTPATTERN = 0,
  SOURCE_SPLASH = 1,
};

void video_init(void);
void video_set_source(int source);
void video_request_osd_toggle(void);
uint32_t video_get_frame_counter(void);
void video_vsync_tick(void);
void video_render_scanline(uint16_t y, uint16_t *line_out, uint16_t width);

#endif
