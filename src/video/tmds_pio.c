#include "tmds_pio.h"

#include "board_pins.h"
#include "log.h"

void tmds_pio_init_640x480(void) {
  (void)PIN_DVI_D2_P;
  (void)PIN_DVI_D2_N;
  (void)PIN_DVI_D1_P;
  (void)PIN_DVI_D1_N;
  (void)PIN_DVI_D0_P;
  (void)PIN_DVI_D0_N;
  (void)PIN_DVI_CLK_P;
  (void)PIN_DVI_CLK_N;
  log_write("video: DVI TMDS init 640x480p60\n");
}
