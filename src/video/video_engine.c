#include "video/video_engine.h"

#include <stdbool.h>

#include "status.h"
#include "video/osd.h"
#include "video/patterns.h"
#include "video/scale.h"
#include "video/tmds_pio.h"

static volatile uint32_t g_frame_counter;
static volatile bool g_osd_enabled;
static volatile bool g_osd_toggle_pending;
static volatile int g_source;

void video_init(void) {
  g_frame_counter = 0;
  g_osd_enabled = false;
  g_osd_toggle_pending = false;
  g_source = SOURCE_TESTPATTERN;
  tmds_pio_init();
  tmds_pio_start();
}

void video_set_source(int source) {
  if (source == SOURCE_TESTPATTERN || source == SOURCE_SPLASH) {
    g_source = source;
  }
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

void video_render_scanline(uint16_t y, uint16_t *line_out, uint16_t width) {
  if (g_source == SOURCE_SPLASH && scale_has_splash()) {
    scale_render_2x(y, line_out, width);
  } else {
    patterns_render_colorbars(y, line_out, width, g_frame_counter);
  }

  system_status_t st;
  status_get(&st);
  osd_compose_scanline(y, line_out, width, &st, g_frame_counter, g_osd_enabled);
}
