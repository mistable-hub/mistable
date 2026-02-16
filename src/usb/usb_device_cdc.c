#include "usb_device_cdc.h"

#include <stdio.h>

void usb_device_cdc_init(void) {
}

void usb_device_cdc_write(const char *data, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    putchar((int)data[i]);
  }
  fflush(stdout);
}
