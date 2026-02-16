#include "usb_host_piousb.h"

#include <stdint.h>

#include "hid_keyboard.h"
#include "piousb_host.pio.h"

static uint32_t poll_counter;
static int announced;

void usb_host_piousb_init(void) {
  poll_counter = 0;
  announced = 0;
}

void usb_host_piousb_poll(void) {
  poll_counter++;
  if (!announced && poll_counter > 20) {
    announced = 1;
    hid_keyboard_on_connect();
  }
  if (announced && (poll_counter % 500) == 0) {
    hid_keyboard_on_key(0x04);
  }
}
