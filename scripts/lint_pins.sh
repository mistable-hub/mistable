#!/usr/bin/env bash
set -euo pipefail

status=0
files=$(find src -type f \( -name '*.c' -o -name '*.h' \))

for f in $files; do
  if [[ "$f" == "src/board_pins.h" ]]; then
    continue
  fi
  if grep -nE 'GPIO[0-9]+' "$f" | grep -v 'DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP\.'; then
    echo "lint_pins: raw GPIO literal found in $f"
    status=1
  fi
  if grep -nE 'gpio_init\([[:space:]]*[0-9]+' "$f"; then
    echo "lint_pins: gpio_init numeric literal found in $f"
    status=1
  fi
  if grep -nE 'PIN_[A-Z0-9_]+[[:space:]]*=[[:space:]]*[0-9]+' "$f"; then
    echo "lint_pins: pin macro redefinition found in $f"
    status=1
  fi
done

if [[ $status -ne 0 ]]; then
  exit 1
fi

echo "lint_pins: PASS"
