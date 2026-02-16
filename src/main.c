#include "FreeRTOS.h"
#include "task.h"
#include "board_pins.h"
#include "log.h"
#include "status.h"
#include "video/video_engine.h"
#include "video/tmds_pio.h"
#include "usb/usb_device_cdc.h"
#include "usb/usb_host_piousb.h"
#include "storage/sd_spi.h"
#include "storage/ff_port.h"
#include "storage/splash.h"
#include "pico/stdlib.h"
#include <stdio.h>

static void print_pin_map(void) {
  log_write("PIN MAP\n");
  log_printf("DVI D2 P/N: %u/%u\n", PIN_DVI_D2_P, PIN_DVI_D2_N);
  log_printf("DVI D1 P/N: %u/%u\n", PIN_DVI_D1_P, PIN_DVI_D1_N);
  log_printf("DVI D0 P/N: %u/%u\n", PIN_DVI_D0_P, PIN_DVI_D0_N);
  log_printf("DVI CLK P/N: %u/%u\n", PIN_DVI_CLK_P, PIN_DVI_CLK_N);
  log_printf("DVI SDA/SCL/CEC: %u/%u/%u\n", PIN_DVI_SDA, PIN_DVI_SCL, PIN_DVI_CEC);
  log_printf("SD SPI SCK/MOSI/MISO/CS: %u/%u/%u/%u\n", PIN_SD_SCK, PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_CS);
  log_printf("PIO-USB DP/DM: %u/%u\n", PIN_PIO_USB_DP, PIN_PIO_USB_DM);
  log_write(PINMAP_DDC_WARNING "\n");
}

static void task_log_flush(void *param) {
  (void)param;
  for (;;) {
    usb_cdc_poll();
    log_flush();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

static void task_usb_host(void *param) {
  (void)param;
  for (;;) {
    usb_host_task();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

static void task_storage(void *param) {
  (void)param;
  sd_spi_init();
  ff_port_init();
  for (;;) {
    if (sd_spi_mount()) {
      status_set_sd_state(SD_STATE_MOUNTED);
      if (splash_load_from_fs()) {
        status_set_sd_state(SD_STATE_SPLASH_OK);
        video_set_source(SOURCE_SPLASH);
      } else {
        status_set_sd_state(SD_STATE_SPLASH_FAIL);
        log_write("splash load failed\n");
      }
    } else {
      status_set_sd_state(SD_STATE_MOUNT_FAIL);
      log_write("sd mount failed\n");
    }
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

static void task_status(void *param) {
  (void)param;
  TickType_t last = 0;
  uint32_t seconds = 0;
  for (;;) {
    TickType_t now = xTaskGetTickCount();
    if (now - last >= pdMS_TO_TICKS(1000)) {
      last = now;
      seconds++;
      status_set_uptime(seconds);
      log_write("heartbeat\n");
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

int main(void) {
  stdio_init_all();
  usb_cdc_init();
  log_init();
  status_init();

  log_write("mistable_phase1\n");
  log_printf("build: %s %s\n", __DATE__, __TIME__);
  print_pin_map();

  video_init();
  tmds_pio_init();
  usb_host_init();

  xTaskCreate(task_log_flush, "log", 512, NULL, 1, NULL);
  xTaskCreate(task_usb_host, "usb", 512, NULL, 1, NULL);
  xTaskCreate(task_storage, "storage", 1024, NULL, 1, NULL);
  xTaskCreate(task_status, "status", 512, NULL, 1, NULL);

  vTaskStartScheduler();
  for (;;) {
  }
}
