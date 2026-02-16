#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

typedef enum {
  SD_STATE_NO_CARD = 0,
  SD_STATE_MOUNT_FAIL,
  SD_STATE_MOUNTED,
  SD_STATE_SPLASH_OK,
  SD_STATE_SPLASH_FAIL
} sd_state_t;

typedef enum {
  KB_STATE_DISCONNECTED = 0,
  KB_STATE_CONNECTED
} kb_state_t;

typedef struct {
  uint32_t uptime_seconds;
  sd_state_t sd_state;
  kb_state_t kb_state;
} shared_status_t;

void status_init(void);
void status_set_uptime(uint32_t seconds);
void status_set_sd_state(sd_state_t state);
void status_set_kb_state(kb_state_t state);
shared_status_t status_snapshot(void);

#endif
