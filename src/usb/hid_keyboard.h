#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

#define HID_KEY_F12 0x45

bool hid_keyboard_is_f12(uint8_t hid_keycode);

#endif
