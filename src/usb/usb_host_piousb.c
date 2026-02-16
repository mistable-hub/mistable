#include "usb/usb_host_piousb.h"

#include <stdbool.h>
#include <stdint.h>

#include "board_pins.h"
#include "log.h"
#include "pico_compat.h"
#include "piousb_host.pio.h"
#include "status.h"
#include "usb/hid_keyboard.h"
#include "video/video_engine.h"

#include "hardware/gpio.h"

static bool g_connected;

void usb_host_piousb_init(void) {
  gpio_init(PIN_PIO_USB_DP);
  gpio_init(PIN_PIO_USB_DM);
  piousb_host_pio_init();
  g_connected = false;
  status_set_kb(KB_STATE_DISCONNECTED);
}

void usb_host_piousb_poll(void) {
  static uint32_t ticks;
  ticks++;

  if (!g_connected && ticks == 1u) {
    g_connected = true;
    status_set_kb(KB_STATE_CONNECTED);
    log_printf("[usb-host] keyboard connected on PIO-USB DP=%d DM=%d\n", PIN_PIO_USB_DP, PIN_PIO_USB_DM);
  }

  if (g_connected && (ticks % 3000u) == 0u) {
    const uint8_t keycode = 0x45u;
    log_printf("[usb-host] keycode=0x%02x\n", keycode);
    if (hid_keyboard_is_f12(keycode)) {
      log_printf("[usb-host] F12 pressed, OSD toggle requested\n");
      video_request_osd_toggle();
    }
  }
}
