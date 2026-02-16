#include "status.h"

static volatile system_status_t g_status;

void status_init(void) {
  g_status.uptime_seconds = 0;
  g_status.sd_state = SD_STATE_NO_CARD;
  g_status.kb_state = KB_STATE_DISCONNECTED;
}

void status_set_sd(sd_state_t state) {
  g_status.sd_state = state;
}

void status_set_kb(kb_state_t state) {
  g_status.kb_state = state;
}

void status_set_uptime(uint32_t uptime_seconds) {
  g_status.uptime_seconds = uptime_seconds;
}

void status_get(system_status_t *out) {
  if (out == 0) {
    return;
  }
  out->uptime_seconds = g_status.uptime_seconds;
  out->sd_state = g_status.sd_state;
  out->kb_state = g_status.kb_state;
}
