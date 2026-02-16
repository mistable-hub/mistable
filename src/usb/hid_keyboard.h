#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include <stdint.h>

void hid_keyboard_on_connect(void);
void hid_keyboard_on_disconnect(void);
void hid_keyboard_on_key(uint8_t keycode);

#endif
