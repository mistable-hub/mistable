#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

typedef enum {
  SD_NO_CARD = 0,
  SD_MOUNT_FAIL,
  SD_MOUNTED,
  SD_SPLASH_OK,
  SD_SPLASH_FAIL
} sd_state_t;

typedef enum {
  KB_DISCONNECTED = 0,
  KB_CONNECTED
} kb_state_t;

typedef struct {
  uint32_t uptime_seconds;
  sd_state_t sd_state;
  kb_state_t kb_state;
} app_status_t;

void status_init(void);
void status_tick_100ms(void);
void status_set_sd(sd_state_t state);
void status_set_kb(kb_state_t state);
app_status_t status_get(void);

#endif
