#include "usb_host_piousb.h"
#include "hid_keyboard.h"
#include "log.h"
#include "status.h"
#include "video/video_engine.h"
#include "board_pins.h"

static void on_key(uint8_t keycode, bool pressed) {
  if (pressed) {
    log_printf("key: 0x%02x\n", keycode);
    if (keycode == HID_KEY_F12) {
      video_request_osd_toggle();
    }
  }
}

static void report_connected(bool connected) {
  if (connected) {
    log_write("kb: connected\n");
    status_set_kb_state(KB_STATE_CONNECTED);
  } else {
    log_write("kb: disconnected\n");
    status_set_kb_state(KB_STATE_DISCONNECTED);
  }
}

void usb_host_init(void) {
  (void)PIN_PIO_USB_DP;
  (void)PIN_PIO_USB_DM;
  hid_keyboard_init(on_key);
  report_connected(false);
}

void usb_host_task(void) {
  hid_keyboard_poll();
}
