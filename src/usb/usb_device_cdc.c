#include "usb_device_cdc.h"

#include <stdio.h>

void usb_device_cdc_init(void) {
}

void usb_device_cdc_write(const char *buf, size_t len) {
  fwrite(buf, 1, len, stdout);
}
