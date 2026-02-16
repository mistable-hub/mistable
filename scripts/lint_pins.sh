#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

raw_gpio_hits=$(grep -RInE 'GPIO[0-9]+' "$ROOT_DIR/src" --exclude='board_pins.h' | grep -v 'DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP.' || true)
num_init_hits=$(grep -RInE 'gpio_(init|set_function|pull_up|pull_down|set_dir)\s*\(\s*[0-9]+' "$ROOT_DIR/src" --exclude='board_pins.h' || true)

if [[ -n "$raw_gpio_hits" || -n "$num_init_hits" ]]; then
  echo "Pin lint failed. Use board_pins.h macros only."
  [[ -n "$raw_gpio_hits" ]] && echo "$raw_gpio_hits"
  [[ -n "$num_init_hits" ]] && echo "$num_init_hits"
  exit 1
fi

echo "Pin lint passed."
