#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)

BAD_GPIO=$(grep -R --line-number -E 'GPIO[0-9]+' "${ROOT_DIR}/src" | grep -v "board_pins.h" || true)
BAD_INIT=$(grep -R --line-number -E 'gpio_init\s*\(\s*[0-9]+' "${ROOT_DIR}/src" | grep -v "board_pins.h" || true)

if [[ -n "${BAD_GPIO}" || -n "${BAD_INIT}" ]]; then
  echo "ERROR: Raw GPIO numbers detected. Use macros from src/board_pins.h" >&2
  if [[ -n "${BAD_GPIO}" ]]; then
    echo "${BAD_GPIO}" >&2
  fi
  if [[ -n "${BAD_INIT}" ]]; then
    echo "${BAD_INIT}" >&2
  fi
  exit 1
fi

echo "Pin lint OK"
