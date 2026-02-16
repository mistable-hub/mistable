#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "FreeRTOS.h"
#include "board_pins.h"
#include "log.h"
#include "status.h"
#include "storage/sd_spi.h"
#include "storage/splash.h"
#include "task.h"
#include "usb/usb_device_cdc.h"
#include "usb/usb_host_piousb.h"
#include "video/video_engine.h"

static void print_pin_map(void) {
  log_printf("PIN MAP");
  log_printf("DVI: D2(%d,%d) D1(%d,%d) D0(%d,%d) CLK(%d,%d)", PIN_DVI_D2_P, PIN_DVI_D2_N,
             PIN_DVI_D1_P, PIN_DVI_D1_N, PIN_DVI_D0_P, PIN_DVI_D0_N, PIN_DVI_CLK_P, PIN_DVI_CLK_N);
  log_printf("DVI SIDEBAND: SDA=%d SCL=%d CEC=%d (disabled)", PIN_DVI_SDA, PIN_DVI_SCL, PIN_DVI_CEC);
  log_printf("SD SPI0: SCK=%d MOSI=%d MISO=%d CS=%d", PIN_SD_SCK, PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_CS);
  log_printf("PIO USB HOST: DP=%d DM=%d", PIN_PIO_USB_DP, PIN_PIO_USB_DM);
  log_printf("DVI DDC/EDID disabled because GPIO%u is used for PIO-USB DP.",
             (unsigned)PIN_PIO_USB_DP);
}

static void task_log_flush(void *arg) {
  (void)arg;
  for (;;) {
    usb_device_cdc_flush();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

static void task_usb_host(void *arg) {
  (void)arg;
  for (;;) {
    usb_host_piousb_poll();
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

static void task_storage(void *arg) {
  (void)arg;
  for (;;) {
    if (sd_spi_mount() != 0) {
      status_set_sd_state(SD_STATE_MOUNT_FAIL);
      log_printf("SD: mount failed, staying on test pattern");
      video_set_source(SOURCE_TESTPATTERN);
      vTaskDelay(pdMS_TO_TICKS(5000));
      continue;
    }

    status_set_sd_state(SD_STATE_MOUNTED);
    int rc = splash_load();
    if (rc == 0) {
      status_set_sd_state(SD_STATE_SPLASH_OK);
      video_set_source(SOURCE_SPLASH);
      log_printf("SD: splash.raw loaded (320x240 RGB565), source=splash 2x");
      vTaskDelay(pdMS_TO_TICKS(5000));
    } else {
      status_set_sd_state(SD_STATE_SPLASH_FAIL);
      log_printf("SD: splash load failed rc=%d, staying test pattern", rc);
      video_set_source(SOURCE_TESTPATTERN);
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
  }
}

static void task_status(void *arg) {
  (void)arg;
  uint32_t ticks = 0;
  for (;;) {
    ticks++;
    if ((ticks % 10) == 0) {
      status_set_uptime(ticks / 10);
      log_printf("heartbeat %lu", (unsigned long)(ticks / 10));
    }
    if ((ticks % 2) == 0) {
      video_tick_vsync();
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

int main(void) {
  log_init();
  status_init();
  video_init();
  usb_device_cdc_init();
  usb_host_piousb_init();

  log_printf("mistable_phase1");
  log_printf("build: %s %s", __DATE__, __TIME__);
  print_pin_map();

  xTaskCreate(task_log_flush, "log", 512, NULL, 3, NULL);
  xTaskCreate(task_usb_host, "usb", 512, NULL, 2, NULL);
  xTaskCreate(task_storage, "storage", 1024, NULL, 2, NULL);
  xTaskCreate(task_status, "status", 512, NULL, 1, NULL);

  vTaskStartScheduler();
  return 0;
}
