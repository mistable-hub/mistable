#ifndef USB_DEVICE_CDC_H
#define USB_DEVICE_CDC_H

#include <stddef.h>
#include <stdint.h>

void usb_cdc_init(void);
void usb_cdc_write(const char *data, size_t len);
void usb_cdc_poll(void);

#endif
