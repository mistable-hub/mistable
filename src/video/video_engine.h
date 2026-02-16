#ifndef VIDEO_ENGINE_H
#define VIDEO_ENGINE_H

#include <stdint.h>

enum {
  SOURCE_TESTPATTERN = 0,
  SOURCE_SPLASH = 1
};

void video_init(void);
void video_set_source(int source);
void video_request_osd_toggle(void);
uint32_t video_get_frame_counter(void);
void video_tick_vsync(void);
int video_osd_enabled(void);
int video_get_source(void);

#endif
