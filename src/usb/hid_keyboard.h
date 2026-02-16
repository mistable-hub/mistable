#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

#define HID_KEY_F12 0x45

typedef void (*hid_key_callback_t)(uint8_t keycode, bool pressed);

void hid_keyboard_init(hid_key_callback_t cb);
void hid_keyboard_poll(void);
void hid_keyboard_simulate_key(uint8_t keycode, bool pressed);

#endif
