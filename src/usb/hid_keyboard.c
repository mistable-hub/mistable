#include "hid_keyboard.h"

bool hid_keyboard_is_f12(uint8_t hid_keycode) {
  return hid_keycode == HID_KEY_F12;
}
