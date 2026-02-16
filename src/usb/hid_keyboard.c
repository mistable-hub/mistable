#include "hid_keyboard.h"

static hid_key_callback_t s_cb;

void hid_keyboard_init(hid_key_callback_t cb) {
  s_cb = cb;
}

void hid_keyboard_poll(void) {
}

void hid_keyboard_simulate_key(uint8_t keycode, bool pressed) {
  if (s_cb) {
    s_cb(keycode, pressed);
  }
}
