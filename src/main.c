#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "board_pins.h"
#include "log.h"
#include "pico/stdlib.h"
#include "status.h"
#include "storage/sd_spi.h"
#include "storage/splash.h"
#include "usb/usb_device_cdc.h"
#include "usb/usb_host_piousb.h"
#include "video/scale.h"
#include "video/video_engine.h"

static void print_pin_map(void) {
  log_write("PIN MAP\n");
  log_printf(" DVI D2+ %d D2- %d D1+ %d D1- %d D0+ %d D0- %d CLK+ %d CLK- %d\n",
             PIN_DVI_D2_P, PIN_DVI_D2_N, PIN_DVI_D1_P, PIN_DVI_D1_N,
             PIN_DVI_D0_P, PIN_DVI_D0_N, PIN_DVI_CLK_P, PIN_DVI_CLK_N);
  log_printf(" DVI sidebands SDA %d SCL %d CEC %d (disabled)\n", PIN_DVI_SDA, PIN_DVI_SCL, PIN_DVI_CEC);
  log_printf(" SD SPI0 SCK %d MOSI %d MISO %d CS %d\n", PIN_SD_SCK, PIN_SD_MOSI, PIN_SD_MISO, PIN_SD_CS);
  log_printf(" PIO-USB DP %d DM %d\n", PIN_PIO_USB_DP, PIN_PIO_USB_DM);
  log_write(" DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP.\n");
}

static void task_log_flush(void *unused) {
  (void)unused;
  char line[256];
  for (;;) {
    while (log_try_pop_line(line, sizeof(line))) {
      usb_device_cdc_write(line, strlen(line));
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

static void task_usb_host(void *unused) {
  (void)unused;
  usb_host_piousb_init();
  for (;;) {
    usb_host_piousb_poll();
    vTaskDelay(pdMS_TO_TICKS(1));
  }
}

static void task_storage(void *unused) {
  (void)unused;
  for (;;) {
    if (!sd_spi_init_and_mount()) {
      status_set_sd(SD_STATE_MOUNT_FAIL);
      vTaskDelay(pdMS_TO_TICKS(5000));
      continue;
    }

    status_set_sd(SD_STATE_MOUNTED);
    if (splash_try_load()) {
      status_set_sd(SD_STATE_SPLASH_OK);
      scale_set_splash(splash_pixels(), true);
      video_set_source(SOURCE_SPLASH);
      return;
    }

    status_set_sd(SD_STATE_SPLASH_FAIL);
    log_write("[sd] splash load failed; keeping test pattern\n");
    video_set_source(SOURCE_TESTPATTERN);
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

static void task_status(void *unused) {
  (void)unused;
  uint32_t ticks_10hz = 0;
  uint16_t scanline[640];

  for (;;) {
    const uint32_t seconds = ticks_10hz / 10u;
    status_set_uptime(seconds);
    video_vsync_tick();
    for (uint16_t y = 0; y < 480u; ++y) {
      video_render_scanline(y, scanline, 640u);
    }
    if ((ticks_10hz % 10u) == 0u) {
      log_printf("[hb] uptime=%lu frame=%lu\n", (unsigned long)seconds, (unsigned long)video_get_frame_counter());
    }
    ticks_10hz++;
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

int main(void) {
  stdio_init_all();
  usb_device_cdc_init();
  log_init();
  status_init();
  video_init();

  log_write("mistable_phase1\n");
  log_printf("build %s %s\n", __DATE__, __TIME__);
  print_pin_map();

  xTaskCreate(task_log_flush, "log_flush", 512, 0, 3, 0);
  xTaskCreate(task_usb_host, "usb_host", 1024, 0, 2, 0);
  xTaskCreate(task_storage, "storage", 1024, 0, 2, 0);
  xTaskCreate(task_status, "status", 1024, 0, 1, 0);
  vTaskStartScheduler();

  for (;;) {
    sleep_ms(1000);
  }

  return 0;
}
