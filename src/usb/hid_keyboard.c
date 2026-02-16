#include "hid_keyboard.h"

#include "log.h"
#include "status.h"
#include "video_engine.h"

#define HID_KEY_F12 0x45

void hid_keyboard_on_connect(void) {
  status_set_kb_state(KB_STATE_CONNECTED);
  log_printf("KB: connected");
}

void hid_keyboard_on_disconnect(void) {
  status_set_kb_state(KB_STATE_DISCONNECTED);
  log_printf("KB: disconnected");
}

void hid_keyboard_on_key(uint8_t keycode) {
  log_printf("KB: keycode=0x%02x", (unsigned)keycode);
  if (keycode == HID_KEY_F12) {
    video_request_osd_toggle();
    log_printf("KB: F12 received, OSD toggle queued for VSYNC");
  }
}
