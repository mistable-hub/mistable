#include "status.h"

#include <pthread.h>

static shared_status_t g_status;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

void status_init(void) {
  pthread_mutex_lock(&g_lock);
  g_status.uptime_seconds = 0;
  g_status.sd_state = SD_STATE_NO_CARD;
  g_status.kb_state = KB_STATE_DISCONNECTED;
  pthread_mutex_unlock(&g_lock);
}

void status_set_uptime(uint32_t seconds) {
  pthread_mutex_lock(&g_lock);
  g_status.uptime_seconds = seconds;
  pthread_mutex_unlock(&g_lock);
}

void status_set_sd_state(sd_state_t state) {
  pthread_mutex_lock(&g_lock);
  g_status.sd_state = state;
  pthread_mutex_unlock(&g_lock);
}

void status_set_kb_state(kb_state_t state) {
  pthread_mutex_lock(&g_lock);
  g_status.kb_state = state;
  pthread_mutex_unlock(&g_lock);
}

shared_status_t status_snapshot(void) {
  shared_status_t copy;
  pthread_mutex_lock(&g_lock);
  copy = g_status;
  pthread_mutex_unlock(&g_lock);
  return copy;
}
