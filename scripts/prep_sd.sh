#!/usr/bin/env bash
set -euo pipefail

if [[ ! -d assets/sdroot ]]; then
  echo "ERROR: assets/sdroot missing"
  exit 1
fi

if command -v lsblk >/dev/null 2>&1; then
  echo "Detected removable block devices:"
  lsblk -o NAME,SIZE,TYPE,MOUNTPOINT,MODEL,RM | awk 'NR==1 || $6==1'
else
  echo "lsblk not available; cannot auto-detect SD devices."
fi

echo
read -r -p "Enter target device (example: /dev/sdb), or leave blank to print manual commands: " DEV
if [[ -z "${DEV}" ]]; then
  echo "Manual workflow:"
  echo "  sudo umount ${DEV}*"
  echo "  sudo mkfs.fat -F 32 ${DEV}"
  echo "  mkdir -p /tmp/mistable_sd && sudo mount ${DEV} /tmp/mistable_sd"
  echo "  sudo cp -v assets/sdroot/* /tmp/mistable_sd/"
  echo "  sync && sudo umount /tmp/mistable_sd"
  exit 0
fi

if ! command -v sudo >/dev/null 2>&1; then
  echo "sudo not available; run these manually:"
  echo "  umount ${DEV}*"
  echo "  mkfs.fat -F 32 ${DEV}"
  echo "  mount ${DEV} /mnt"
  echo "  cp -v assets/sdroot/* /mnt/"
  echo "  sync && umount /mnt"
  exit 1
fi

if ! command -v mkfs.fat >/dev/null 2>&1; then
  echo "mkfs.fat missing. Install with: sudo apt-get install dosfstools"
  exit 1
fi

echo "About to erase ${DEV}."
read -r -p "Type YES to continue: " CONFIRM
if [[ "${CONFIRM}" != "YES" ]]; then
  echo "Cancelled."
  exit 1
fi

sudo umount "${DEV}"* || true
sudo mkfs.fat -F 32 "${DEV}"
MNT="/tmp/mistable_sd_$$"
mkdir -p "${MNT}"
sudo mount "${DEV}" "${MNT}"
sudo cp -v assets/sdroot/* "${MNT}/"
sync
sudo umount "${MNT}"
rmdir "${MNT}"
echo "SD card prepared."
