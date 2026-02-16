#include "status.h"

static status_t s_status;

void status_init(void) {
  s_status.uptime_seconds = 0;
  s_status.sd_state = SD_STATE_NO_CARD;
  s_status.kb_state = KB_STATE_DISCONNECTED;
}

void status_set_sd_state(sd_state_t state) {
  s_status.sd_state = state;
}

void status_set_kb_state(kb_state_t state) {
  s_status.kb_state = state;
}

void status_set_uptime(uint32_t seconds) {
  s_status.uptime_seconds = seconds;
}

status_t status_get(void) {
  return s_status;
}
