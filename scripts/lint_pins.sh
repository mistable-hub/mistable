#!/usr/bin/env bash
set -euo pipefail

fail=0

if grep -RInE 'GPIO[0-9]+' src --include='*.[ch]' --exclude='board_pins.h'; then
  echo "ERROR: raw GPIO token found outside src/board_pins.h"
  fail=1
fi

if grep -RInE 'gpio_init\([[:space:]]*[0-9]+' src --include='*.[ch]' --exclude='board_pins.h'; then
  echo "ERROR: gpio_init() with numeric literal found outside src/board_pins.h"
  fail=1
fi

exit ${fail}
