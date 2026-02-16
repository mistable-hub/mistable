#!/usr/bin/env bash
set -euo pipefail

if [[ ! -d assets/sdroot ]]; then
  echo "assets/sdroot missing"
  exit 1
fi

if ! command -v lsblk >/dev/null 2>&1; then
  echo "lsblk not found. Manual fallback:"
  echo "1) Format SD as FAT32"
  echo "2) Copy assets/sdroot/* to SD root"
  exit 0
fi

echo "Available removable block devices:"
lsblk -dpno NAME,SIZE,MODEL,RM | awk '$4==1 {print}'

echo
read -r -p "Enter target device path (example /dev/sdb): " dev
if [[ -z "${dev}" || ! -b "${dev}" ]]; then
  echo "Invalid device"
  exit 1
fi

read -r -p "Type YES to confirm formatting ${dev}: " confirm
if [[ "$confirm" != "YES" ]]; then
  echo "Cancelled"
  exit 1
fi

if command -v sudo >/dev/null 2>&1; then
  if ! command -v mkfs.fat >/dev/null 2>&1; then
    echo "mkfs.fat missing. Install: sudo apt-get install dosfstools"
    exit 1
  fi
  part="${dev}1"
  sudo umount "${part}" >/dev/null 2>&1 || true
  sudo mkfs.fat -F 32 "${part}"
  mnt=$(mktemp -d)
  sudo mount "${part}" "$mnt"
  sudo cp -v assets/sdroot/* "$mnt"/
  sync
  sudo umount "$mnt"
  rmdir "$mnt"
  echo "SD prepared successfully"
else
  echo "sudo not available. Run these commands manually:"
  echo "  mkfs.fat -F 32 ${dev}1"
  echo "  mount ${dev}1 /mnt"
  echo "  cp -v assets/sdroot/* /mnt/"
  echo "  umount /mnt"
fi
