#include "usb_host_piousb.h"

#include "board_pins.h"

static int g_connected;

void usb_host_piousb_init(void) {
  (void)PIN_PIO_USB_DP;
  (void)PIN_PIO_USB_DM;
  g_connected = 0;
}

void usb_host_piousb_poll(void) {
}

int usb_host_keyboard_connected(void) {
  return g_connected;
}
