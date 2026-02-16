#include "video_engine.h"

#include <stdbool.h>
#include <stdint.h>

static volatile uint32_t frame_counter;
static volatile bool osd_enabled;
static volatile bool osd_toggle_pending;
static volatile int source_id;

void video_init(void) {
  frame_counter = 0;
  osd_enabled = false;
  osd_toggle_pending = false;
  source_id = SOURCE_TESTPATTERN;
}

void video_set_source(int source) {
  source_id = source;
  (void)source_id;
}

void video_request_osd_toggle(void) {
  osd_toggle_pending = true;
}

uint32_t video_get_frame_counter(void) {
  return frame_counter;
}

void video_vsync_tick(void) {
  frame_counter++;
  if (osd_toggle_pending) {
    osd_enabled = !osd_enabled;
    osd_toggle_pending = false;
  }
  (void)osd_enabled;
}
