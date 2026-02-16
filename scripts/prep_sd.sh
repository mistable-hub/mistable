#!/usr/bin/env bash
set -euo pipefail

if [[ ! -d assets/sdroot ]]; then
  echo "ERROR: assets/sdroot missing"
  exit 1
fi

if ! command -v lsblk >/dev/null 2>&1; then
  echo "ERROR: lsblk required. Install util-linux."
  exit 1
fi

echo "Detected block devices:"
lsblk -o NAME,SIZE,TYPE,MOUNTPOINT,MODEL

if ! command -v mkfs.fat >/dev/null 2>&1; then
  echo "mkfs.fat not found. Install: sudo apt-get install -y dosfstools"
  echo "Manual fallback: format SD as FAT32 and copy assets/sdroot/* to card root"
  exit 0
fi

if ! command -v sudo >/dev/null 2>&1; then
  echo "sudo unavailable. Manual commands:"
  echo "  sudo mkfs.fat -F 32 /dev/sdX1"
  echo "  mkdir -p /tmp/mistable_sd && sudo mount /dev/sdX1 /tmp/mistable_sd"
  echo "  sudo cp -av assets/sdroot/* /tmp/mistable_sd/"
  echo "  sync && sudo umount /tmp/mistable_sd"
  exit 0
fi

read -r -p "Enter target SD partition (example /dev/sdb1): " target
if [[ -z "$target" ]]; then
  echo "No device entered"
  exit 1
fi

read -r -p "Type ERASE to format ${target}: " confirm
if [[ "$confirm" != "ERASE" ]]; then
  echo "Cancelled"
  exit 1
fi

sudo mkfs.fat -F 32 "$target"
mount_dir="/tmp/mistable_sd"
mkdir -p "$mount_dir"
sudo mount "$target" "$mount_dir"
sudo cp -av assets/sdroot/* "$mount_dir/"
sync
sudo umount "$mount_dir"
echo "SD prepared: $target"
