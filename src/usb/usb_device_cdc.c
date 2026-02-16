#include "usb_device_cdc.h"

#include <stdio.h>

void usb_device_cdc_init(void) {
}

void usb_device_cdc_write(const char *msg) {
  if (msg != 0) {
    fputs(msg, stdout);
    fflush(stdout);
  }
}
