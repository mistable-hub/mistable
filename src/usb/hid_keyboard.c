#include "hid_keyboard.h"

static int g_mock_f12;

int hid_keyboard_f12_pressed(void) {
  int pressed = g_mock_f12;
  g_mock_f12 = 0;
  return pressed;
}

void hid_keyboard_set_mock_f12(int pressed) {
  g_mock_f12 = pressed;
}
