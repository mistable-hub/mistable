#ifndef USB_DEVICE_CDC_H
#define USB_DEVICE_CDC_H

#include <stddef.h>

void usb_device_cdc_init(void);
void usb_device_cdc_write(const char *data, size_t len);

#endif
