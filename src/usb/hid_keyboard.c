#include "usb/hid_keyboard.h"

bool hid_keyboard_is_f12(uint8_t keycode) {
  return keycode == 0x45u;
}
