#include "video_engine.h"
#include "patterns.h"
#include "osd.h"
#include "scale.h"
#include "storage/splash.h"

static volatile uint32_t s_frame_counter = 0;
static volatile bool s_osd_enabled = false;
static volatile bool s_osd_toggle_pending = false;
static video_source_t s_source = SOURCE_TESTPATTERN;

void video_init(void) {
  s_frame_counter = 0;
  s_osd_enabled = false;
  s_osd_toggle_pending = false;
  s_source = SOURCE_TESTPATTERN;
}

void video_set_source(video_source_t source) {
  s_source = source;
}

void video_request_osd_toggle(void) {
  s_osd_toggle_pending = true;
}

uint32_t video_get_frame_counter(void) {
  return s_frame_counter;
}

static void video_apply_vsync(void) {
  if (s_osd_toggle_pending) {
    s_osd_enabled = !s_osd_enabled;
    s_osd_toggle_pending = false;
  }
  s_frame_counter++;
}

void video_scanline_render(uint16_t *line_buf, uint32_t y) {
  if (y == 0) {
    video_apply_vsync();
  }

  if (s_source == SOURCE_SPLASH && splash_is_loaded()) {
    scale_2x_line(line_buf, y, splash_get_pixels());
  } else {
    pattern_colorbars_line(line_buf, y);
  }

  if (s_osd_enabled) {
    osd_render_line(line_buf, y);
  }
}
