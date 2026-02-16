#include "usb_device_cdc.h"

#include <stdio.h>

#include "log.h"

void usb_device_cdc_init(void) {
  log_printf("CDC: ACM online (PRIMARY USB-C)");
}

void usb_device_cdc_flush(void) {
  char out[512];
  size_t n = log_pop(out, sizeof(out));
  if (n > 0) {
    fwrite(out, 1, n, stdout);
    fflush(stdout);
  }
}
