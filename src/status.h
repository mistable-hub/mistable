#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

typedef enum {
  SD_NO_CARD = 0,
  SD_MOUNT_FAIL,
  SD_MOUNTED,
  SD_SPLASH_OK,
  SD_SPLASH_FAIL,
} sd_state_t;

typedef enum {
  KB_DISCONNECTED = 0,
  KB_CONNECTED,
} kb_state_t;

typedef struct {
  uint32_t uptime_seconds;
  sd_state_t sd_state;
  kb_state_t kb_state;
} status_t;

void status_init(void);
status_t status_get(void);
void status_set_uptime(uint32_t seconds);
void status_set_sd(sd_state_t s);
void status_set_kb(kb_state_t s);

#endif
