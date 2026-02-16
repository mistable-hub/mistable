#include "status.h"

#include <string.h>

static volatile status_t g_status;

void status_init(void) {
  status_t init = {0};
  init.sd_state = SD_NO_CARD;
  init.kb_state = KB_DISCONNECTED;
  g_status = init;
}

status_t status_get(void) {
  return g_status;
}

void status_set_uptime(uint32_t seconds) {
  g_status.uptime_seconds = seconds;
}

void status_set_sd(sd_state_t s) {
  g_status.sd_state = s;
}

void status_set_kb(kb_state_t s) {
  g_status.kb_state = s;
}
