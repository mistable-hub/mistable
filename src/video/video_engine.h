#ifndef VIDEO_ENGINE_H
#define VIDEO_ENGINE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  SOURCE_TESTPATTERN = 0,
  SOURCE_SPLASH = 1
} video_source_t;

void video_init(void);
void video_set_source(video_source_t source);
void video_request_osd_toggle(void);
uint32_t video_get_frame_counter(void);

void video_scanline_render(uint16_t *line_buf, uint32_t y);

#endif
