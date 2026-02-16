#ifndef HID_KEYBOARD_H
#define HID_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

bool hid_keyboard_process_report(const uint8_t *report, uint8_t len, bool *f12_pressed);

#endif
