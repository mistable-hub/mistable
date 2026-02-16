#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="assets/sdroot"

if [[ ! -d "$ROOT_DIR" ]]; then
  echo "Missing $ROOT_DIR"
  exit 1
fi

if ! command -v lsblk >/dev/null 2>&1; then
  echo "lsblk missing. Manual fallback:"
  echo "  1) Format SD card FAT32"
  echo "  2) Copy assets/sdroot/* to SD root"
  exit 1
fi

if ! command -v mkfs.fat >/dev/null 2>&1; then
  echo "mkfs.fat missing. Install suggestion (Ubuntu): sudo apt-get install dosfstools"
  echo "Manual fallback: format SD as FAT32, then copy assets/sdroot/*"
  exit 1
fi

echo "Available removable devices:"
lsblk -dpno NAME,SIZE,MODEL,TRAN | sed 's/^/  /'

echo
read -r -p "Enter SD device path (example /dev/sdb): " DEV
if [[ -z "$DEV" || ! -b "$DEV" ]]; then
  echo "Invalid block device"
  exit 1
fi

echo "WARNING: This will format $DEV as FAT32 and erase data."
read -r -p "Type YES to continue: " CONFIRM
if [[ "$CONFIRM" != "YES" ]]; then
  echo "Cancelled"
  exit 1
fi

if command -v sudo >/dev/null 2>&1; then
  sudo umount "${DEV}"* 2>/dev/null || true
  sudo mkfs.fat -F 32 "$DEV"
  MNT="/tmp/mistable_sd_mount"
  mkdir -p "$MNT"
  sudo mount "$DEV" "$MNT"
  sudo cp -v "$ROOT_DIR"/* "$MNT"/
  sync
  sudo umount "$MNT"
  echo "SD prepared: $DEV"
else
  echo "sudo is not available. Run these commands manually:"
  echo "  umount ${DEV}*"
  echo "  mkfs.fat -F 32 ${DEV}"
  echo "  mount ${DEV} /mnt"
  echo "  cp assets/sdroot/* /mnt/"
  echo "  umount /mnt"
fi
