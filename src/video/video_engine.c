#include "video_engine.h"

#include "osd.h"
#include "patterns.h"
#include "scale.h"
#include "tmds_pio.h"

static volatile uint32_t g_frame_counter;
static volatile bool g_osd_enabled;
static volatile bool g_osd_toggle_pending;
static volatile video_source_t g_source;

void video_init(void) {
  g_frame_counter = 0;
  g_osd_enabled = false;
  g_osd_toggle_pending = false;
  g_source = SOURCE_TESTPATTERN;
  tmds_pio_init_640x480();
  patterns_init();
  scale_init();
  osd_init();
}

void video_set_source(video_source_t source) {
  g_source = source;
}

void video_request_osd_toggle(void) {
  g_osd_toggle_pending = true;
}

uint32_t video_get_frame_counter(void) {
  return g_frame_counter;
}

void video_vsync_tick(void) {
  g_frame_counter++;
  if (g_osd_toggle_pending) {
    g_osd_enabled = !g_osd_enabled;
    g_osd_toggle_pending = false;
  }
}

bool video_is_osd_enabled(void) {
  return g_osd_enabled;
}

video_source_t video_get_source(void) {
  return g_source;
}
