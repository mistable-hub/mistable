#!/usr/bin/env bash
set -euo pipefail

if grep -REn 'GPIO[0-9]+' src; then
  echo "Found forbidden raw GPIO token usage"
  exit 1
fi

if grep -REn --exclude='board_pins.h' 'gpio_init\([[:space:]]*[0-9]+' src; then
  echo "Found forbidden numeric gpio_init usage"
  exit 1
fi

echo "lint_pins: OK"
