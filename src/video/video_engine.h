#ifndef VIDEO_ENGINE_H
#define VIDEO_ENGINE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  SOURCE_TESTPATTERN = 0,
  SOURCE_SPLASH
} video_source_t;

void video_init(void);
void video_set_source(video_source_t source);
void video_request_osd_toggle(void);
uint32_t video_get_frame_counter(void);
void video_vsync_tick(void);
bool video_is_osd_enabled(void);
video_source_t video_get_source(void);

#endif
