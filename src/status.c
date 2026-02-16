#include "status.h"

static app_status_t g_status;
static uint32_t g_ticks_100ms;

void status_init(void) {
  g_status.uptime_seconds = 0;
  g_status.sd_state = SD_NO_CARD;
  g_status.kb_state = KB_DISCONNECTED;
  g_ticks_100ms = 0;
}

void status_tick_100ms(void) {
  g_ticks_100ms++;
  if ((g_ticks_100ms % 10u) == 0u) {
    g_status.uptime_seconds++;
  }
}

void status_set_sd(sd_state_t state) {
  g_status.sd_state = state;
}

void status_set_kb(kb_state_t state) {
  g_status.kb_state = state;
}

app_status_t status_get(void) {
  return g_status;
}
