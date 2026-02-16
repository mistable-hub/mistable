#include "FreeRTOS.h"
#include "task.h"

#include "board_pins.h"
#include "log.h"
#include "status.h"
#include "storage/splash.h"
#include "usb/hid_keyboard.h"
#include "usb/usb_device_cdc.h"
#include "usb/usb_host_piousb.h"
#include "video/video_engine.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void print_pin_map(void) {
  log_printf("PIN MAP\n");
  log_printf("DVI D2+/D2-: %d/%d\n", PIN_DVI_D2_P, PIN_DVI_D2_N);
  log_printf("DVI D1+/D1-: %d/%d\n", PIN_DVI_D1_P, PIN_DVI_D1_N);
  log_printf("DVI D0+/D0-: %d/%d\n", PIN_DVI_D0_P, PIN_DVI_D0_N);
  log_printf("DVI CLK+/CLK-: %d/%d\n", PIN_DVI_CLK_P, PIN_DVI_CLK_N);
  log_printf("DVI SDA/SCL/CEC: %d/%d/%d\n", PIN_DVI_SDA, PIN_DVI_SCL, PIN_DVI_CEC);
  log_printf("SD SCK/MOSI/MISO/CS: %d/%d/%d/%d\n", PIN_SD_SCK, PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_CS);
  log_printf("PIO-USB DP/DM: %d/%d\n", PIN_PIO_USB_DP, PIN_PIO_USB_DM);
  log_printf("DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP.\n");
}

static void task_log_flush(void *arg) {
  (void)arg;
  char out[128];
  while (1) {
    size_t n = log_read_chunk(out, sizeof(out));
    if (n > 0) {
      usb_device_cdc_write(out, n);
    }
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}

static void task_usb_host(void *arg) {
  (void)arg;
  usb_host_piousb_init();
  while (1) {
    usb_host_piousb_poll();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

static void task_storage(void *arg) {
  (void)arg;
  while (1) {
    if (splash_load_from_sd()) {
      status_set_sd(SD_SPLASH_OK);
      video_set_source(SOURCE_SPLASH);
      vTaskDelete(NULL);
    }
    status_set_sd(SD_MOUNT_FAIL);
    log_printf("SD mount/load failed; retry in 5s\n");
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

static void task_status(void *arg) {
  (void)arg;
  uint32_t sec = 0;
  while (1) {
    status_set_uptime(sec++);
    log_printf("heartbeat %lu\n", (unsigned long)sec);
    video_vsync_tick();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

int main(void) {
  stdio_init_all();
  log_init();
  status_init();
  usb_device_cdc_init();
  video_init();

  log_printf("mistable_phase1\n");
  log_printf("build %s %s\n", __DATE__, __TIME__);
  print_pin_map();

  xTaskCreate(task_log_flush, "log_flush", 768, NULL, 3, NULL);
  xTaskCreate(task_usb_host, "usb_host", 1024, NULL, 2, NULL);
  xTaskCreate(task_storage, "storage", 1024, NULL, 2, NULL);
  xTaskCreate(task_status, "status", 768, NULL, 1, NULL);

  vTaskStartScheduler();
  while (1) {
  }
}
