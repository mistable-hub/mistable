#include "usb/usb_device_cdc.h"

#include <stdio.h>

void usb_device_cdc_init(void) {
}

void usb_device_cdc_write(const char *data, size_t len) {
  if (data == 0 || len == 0u) {
    return;
  }
  fwrite(data, 1u, len, stdout);
  fflush(stdout);
}
