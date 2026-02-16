#include "FreeRTOS.h"
#include "task.h"

#include "board_pins.h"
#include "log.h"
#include "status.h"
#include "storage/ff_port.h"
#include "storage/splash.h"
#include "usb/hid_keyboard.h"
#include "usb/usb_device_cdc.h"
#include "usb/usb_host_piousb.h"
#include "video/video_engine.h"

#include <stdint.h>

static uint16_t g_splash[SPLASH_WIDTH * SPLASH_HEIGHT];

static const char *sd_state_text(sd_state_t s) {
  switch (s) {
    case SD_NO_CARD: return "NO_CARD";
    case SD_MOUNT_FAIL: return "MOUNT_FAIL";
    case SD_MOUNTED: return "MOUNTED";
    case SD_SPLASH_OK: return "SPLASH_OK";
    case SD_SPLASH_FAIL: return "SPLASH_FAIL";
    default: return "UNKNOWN";
  }
}

static void print_pin_map(void) {
  log_printf("PIN MAP\n");
  log_printf(" DVI D2+:%d D2-:%d D1+:%d D1-:%d D0+:%d D0-:%d CLK+:%d CLK-:%d\n",
             PIN_DVI_D2_P, PIN_DVI_D2_N, PIN_DVI_D1_P, PIN_DVI_D1_N,
             PIN_DVI_D0_P, PIN_DVI_D0_N, PIN_DVI_CLK_P, PIN_DVI_CLK_N);
  log_printf(" DVI sidebands SDA:%d SCL:%d CEC:%d (disabled)\n", PIN_DVI_SDA, PIN_DVI_SCL, PIN_DVI_CEC);
  log_printf(" SD SPI0 SCK:%d MOSI:%d MISO:%d CS:%d\n", PIN_SD_SCK, PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_CS);
  log_printf(" PIO-USB DP:%d DM:%d\n", PIN_PIO_USB_DP, PIN_PIO_USB_DM);
  log_printf(" DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP.\n");
}

static void task_log_flush(void *arg) {
  (void)arg;
  char out[256];
  while (log_has_data()) {
    size_t n = log_drain(out, sizeof(out));
    if (n == 0) {
      break;
    }
    usb_device_cdc_write(out, n);
  }
}

static void task_usb_host(void *arg) {
  (void)arg;
  usb_host_piousb_init();
  usb_host_piousb_poll();
  if (usb_host_keyboard_connected()) {
    status_set_kb(KB_CONNECTED);
    log_printf("KB connected\n");
  } else {
    status_set_kb(KB_DISCONNECTED);
  }

  if (hid_keyboard_f12_pressed()) {
    log_printf("KB F12 -> OSD toggle request\n");
    video_request_osd_toggle();
  }
}

static void task_storage(void *arg) {
  (void)arg;
  if (ff_port_mount() != 0) {
    status_set_sd(SD_MOUNT_FAIL);
    log_printf("SD mount failed; retry in 5s\n");
    return;
  }
  status_set_sd(SD_MOUNTED);
  log_printf("SD mounted\n");

  int rc = splash_load_from_sd(g_splash, SPLASH_WIDTH * SPLASH_HEIGHT);
  if (rc != 0) {
    status_set_sd(SD_SPLASH_FAIL);
    log_printf("splash load failed (%d)\n", rc);
    return;
  }
  status_set_sd(SD_SPLASH_OK);
  video_set_source(SOURCE_SPLASH);
  log_printf("splash loaded (%u bytes)\n", (unsigned)SPLASH_BYTES);
}

static void task_status(void *arg) {
  (void)arg;
  for (int i = 0; i < 20; ++i) {
    status_tick_100ms();
  }
  app_status_t s = status_get();
  log_printf("status: up=%u sd=%s kb=%s\n", s.uptime_seconds, sd_state_text(s.sd_state), s.kb_state == KB_CONNECTED ? "OK" : "NO");
}

int main(void) {
  usb_device_cdc_init();
  log_init();
  status_init();
  video_init();

  log_printf("mistable_phase1\n");
  log_printf("build %s %s\n", __DATE__, __TIME__);
  print_pin_map();

  xTaskCreate(task_log_flush, "log", 512, 0, 2, 0);
  xTaskCreate(task_usb_host, "usb", 1024, 0, 2, 0);
  xTaskCreate(task_storage, "stor", 1024, 0, 2, 0);
  xTaskCreate(task_status, "stat", 512, 0, 1, 0);

  for (int i = 0; i < 10; ++i) {
    video_vsync_step();
    log_printf("heartbeat %d frame=%lu osd=%d src=%d\n", i + 1,
               (unsigned long)video_get_frame_counter(), video_get_osd_enabled(), video_get_source());
  }

  vTaskStartScheduler();
  task_log_flush(0);
  return 0;
}
