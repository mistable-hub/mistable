#include "hid_keyboard.h"

bool hid_keyboard_process_report(const uint8_t *report, uint8_t len, bool *f12_pressed) {
  *f12_pressed = false;
  if (len < 8) {
    return false;
  }
  for (uint8_t i = 2; i < 8; ++i) {
    if (report[i] == 0x45) {
      *f12_pressed = true;
      return true;
    }
  }
  return true;
}
