#ifndef USB_HOST_PIOUSB_H
#define USB_HOST_PIOUSB_H

#include <stdbool.h>

void usb_host_piousb_init(void);
void usb_host_piousb_poll(void);
bool usb_host_keyboard_connected(void);

#endif
