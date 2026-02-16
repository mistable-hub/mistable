#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "pico/stdlib.h"

#include "board_pins.h"
#include "log.h"
#include "status.h"
#include "storage/ff_port.h"
#include "storage/sd_spi.h"
#include "storage/splash.h"
#include "usb/usb_device_cdc.h"
#include "usb/usb_host_piousb.h"
#include "video/video_engine.h"

static void print_pin_map(void) {
  log_write("PIN MAP\n");
  log_write("DVI: D2(32/33) D1(34/35) D0(36/37) CLK(39/38)\n");
  log_write("DVI sidebands: SDA=44 SCL=46 CEC=6 (disabled)\n");
  log_write("SD spi0: SCK=30 MOSI=31 MISO=40 CS=43\n");
  log_write("PIO-USB host: DP=46 DM=47\n");
  log_write("DVI DDC/EDID disabled because GPIO" "46 is used for PIO-USB DP.\n");
}

static void task_log_flush(void *arg) {
  char line[256];
  (void)arg;
  for (int i = 0; i < 20; ++i) {
    while (log_pop(line, sizeof(line))) {
      usb_device_cdc_write(line);
    }
    log_write("heartbeat\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void task_usb_host(void *arg) {
  (void)arg;
  usb_host_piousb_init();
  for (int i = 0; i < 10; ++i) {
    usb_host_piousb_poll();
    vTaskDelay(pdMS_TO_TICKS(50));
  }
}

static void task_storage(void *arg) {
  bool mounted = false;
  (void)arg;
  sd_spi_init();
  for (int retry = 0; retry < 2; ++retry) {
    if (!sd_spi_card_present()) {
      status_set_sd(SD_STATE_NO_CARD);
      log_write("storage: no sd card\n");
      vTaskDelay(pdMS_TO_TICKS(5000));
      continue;
    }
    if (!ff_port_mount()) {
      status_set_sd(SD_STATE_MOUNT_FAIL);
      log_write("storage: mount failed\n");
      vTaskDelay(pdMS_TO_TICKS(5000));
      continue;
    }
    status_set_sd(SD_STATE_MOUNTED);
    mounted = true;
    break;
  }

  if (mounted && splash_load_from_sd()) {
    status_set_sd(SD_STATE_SPLASH_OK);
    video_set_source(SOURCE_SPLASH);
  } else if (mounted) {
    status_set_sd(SD_STATE_SPLASH_FAIL);
  }
}

static void task_status(void *arg) {
  (void)arg;
  for (int i = 0; i < 200; ++i) {
    status_tick_100ms();
    video_vsync_tick();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

int main(void) {
  stdio_init_all();
  usb_device_cdc_init();
  log_init();
  status_init();
  video_init();
  video_set_source(SOURCE_TESTPATTERN);

  log_write("mistable_phase1\n");
  log_write("build: " __DATE__ " " __TIME__ "\n");
  print_pin_map();

  xTaskCreate(task_log_flush, "log", 512, 0, 2, 0);
  xTaskCreate(task_usb_host, "usb_host", 512, 0, 3, 0);
  xTaskCreate(task_storage, "storage", 1024, 0, 2, 0);
  xTaskCreate(task_status, "status", 512, 0, 1, 0);

  vTaskStartScheduler();

  printf("frame_counter=%u osd=%d source=%d uptime=%u sd=%s kb=%s\n",
         (unsigned)video_get_frame_counter(),
         video_is_osd_enabled() ? 1 : 0,
         (int)video_get_source(),
         (unsigned)status_snapshot().uptime_seconds,
         status_sd_text(status_snapshot().sd_state),
         status_kb_text(status_snapshot().kb_state));

  return 0;
}
