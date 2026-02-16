#include "video_engine.h"

#include "osd.h"
#include "patterns.h"
#include "tmds_pio.h"

static uint32_t g_frame_counter;
static int g_source;
static int g_osd_enabled;
static int g_osd_toggle_pending;

void video_init(void) {
  tmds_pio_init();
  patterns_init();
  g_frame_counter = 0;
  g_source = SOURCE_TESTPATTERN;
  g_osd_enabled = 0;
  g_osd_toggle_pending = 0;
}

void video_set_source(int source) {
  g_source = source;
}

void video_request_osd_toggle(void) {
  g_osd_toggle_pending = 1;
}

uint32_t video_get_frame_counter(void) {
  return g_frame_counter;
}

void video_vsync_step(void) {
  g_frame_counter++;
  if (g_osd_toggle_pending) {
    g_osd_enabled = !g_osd_enabled;
    g_osd_toggle_pending = 0;
  }
  osd_set_enabled(g_osd_enabled);
}

int video_get_osd_enabled(void) {
  return g_osd_enabled;
}

int video_get_source(void) {
  return g_source;
}
