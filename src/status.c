#include "status.h"

static shared_status_t g_status;
static uint8_t g_100ms_ticks;

void status_init(void) {
  g_status.uptime_seconds = 0;
  g_status.sd_state = SD_STATE_NO_CARD;
  g_status.kb_state = KB_STATE_DISCONNECTED;
  g_100ms_ticks = 0;
}

void status_set_sd(sd_state_t state) {
  g_status.sd_state = state;
}

void status_set_kb(kb_state_t state) {
  g_status.kb_state = state;
}

void status_tick_100ms(void) {
  g_100ms_ticks++;
  if (g_100ms_ticks >= 10) {
    g_100ms_ticks = 0;
    g_status.uptime_seconds++;
  }
}

shared_status_t status_snapshot(void) {
  return g_status;
}

const char *status_sd_text(sd_state_t state) {
  switch (state) {
    case SD_STATE_MOUNTED:
    case SD_STATE_SPLASH_OK:
      return "MOUNTED";
    default:
      return "NO";
  }
}

const char *status_kb_text(kb_state_t state) {
  return state == KB_STATE_CONNECTED ? "OK" : "NO";
}
