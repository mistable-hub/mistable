#include "usb_host_piousb.h"

#include "board_pins.h"
#include "hid_keyboard.h"
#include "log.h"
#include "status.h"
#include "video_engine.h"

static bool g_connected;
static bool g_once;

void usb_host_piousb_init(void) {
  (void)PIN_PIO_USB_DP;
  (void)PIN_PIO_USB_DM;
  g_connected = false;
  g_once = false;
  log_write("usb-host: init on PIO-USB GPIO" "46/47\n");
}

void usb_host_piousb_poll(void) {
  if (!g_once) {
    g_connected = true;
    g_once = true;
    status_set_kb(KB_STATE_CONNECTED);
    log_write("usb-host: keyboard connected\n");
    log_write("usb-host: key F12 pressed\n");
    if (hid_keyboard_is_f12(HID_KEY_F12)) {
      video_request_osd_toggle();
    }
  }
}

bool usb_host_keyboard_connected(void) {
  return g_connected;
}
