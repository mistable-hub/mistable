#!/usr/bin/env bash
set -euo pipefail

gpio_hits="$(grep -RInE 'GPIO[0-9]+' src --exclude='board_pins.h' || true)"
if [[ -n "${gpio_hits}" ]]; then
  filtered="$(printf '%s\n' "${gpio_hits}" | grep -Fv 'DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP.' || true)"
  if [[ -n "${filtered}" ]]; then
    printf '%s\n' "${filtered}"
    echo "ERROR: raw GPIO literal token found outside src/board_pins.h"
    exit 1
  fi
fi

if grep -RInE 'gpio_init\([[:space:]]*[0-9]+' src --exclude='board_pins.h'; then
  echo "ERROR: gpio_init with numeric literal found outside src/board_pins.h"
  exit 1
fi

echo "pin lint passed"
