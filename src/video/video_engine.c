#include "video_engine.h"

#include <pthread.h>

static pthread_mutex_t vlock = PTHREAD_MUTEX_INITIALIZER;
static uint32_t frame_counter;
static int video_source;
static int osd_enabled;
static int osd_toggle_pending;

void video_init(void) {
  pthread_mutex_lock(&vlock);
  frame_counter = 0;
  video_source = SOURCE_TESTPATTERN;
  osd_enabled = 0;
  osd_toggle_pending = 0;
  pthread_mutex_unlock(&vlock);
}

void video_set_source(int source) {
  pthread_mutex_lock(&vlock);
  video_source = source;
  pthread_mutex_unlock(&vlock);
}

void video_request_osd_toggle(void) {
  pthread_mutex_lock(&vlock);
  osd_toggle_pending = 1;
  pthread_mutex_unlock(&vlock);
}

uint32_t video_get_frame_counter(void) {
  pthread_mutex_lock(&vlock);
  uint32_t value = frame_counter;
  pthread_mutex_unlock(&vlock);
  return value;
}

void video_tick_vsync(void) {
  pthread_mutex_lock(&vlock);
  frame_counter++;
  if (osd_toggle_pending) {
    osd_enabled = !osd_enabled;
    osd_toggle_pending = 0;
  }
  pthread_mutex_unlock(&vlock);
}

int video_osd_enabled(void) {
  pthread_mutex_lock(&vlock);
  int enabled = osd_enabled;
  pthread_mutex_unlock(&vlock);
  return enabled;
}

int video_get_source(void) {
  pthread_mutex_lock(&vlock);
  int source = video_source;
  pthread_mutex_unlock(&vlock);
  return source;
}
