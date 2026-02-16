#include "usb_device_cdc.h"
#include <stdio.h>

void usb_cdc_init(void) {
}

void usb_cdc_write(const char *data, size_t len) {
  if (!data || len == 0) {
    return;
  }
  fwrite(data, 1, len, stdout);
  fflush(stdout);
}

void usb_cdc_poll(void) {
}
