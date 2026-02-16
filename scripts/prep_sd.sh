#!/usr/bin/env bash
set -euo pipefail

if [[ "$(uname -s)" != "Linux" ]]; then
  echo "This script supports Linux only. Manual fallback: copy assets/sdroot/* to FAT SD root."
  exit 0
fi

if ! command -v lsblk >/dev/null 2>&1; then
  echo "lsblk not found. Install util-linux and rerun."
  exit 1
fi

echo "Available block devices:"
lsblk -dpno NAME,SIZE,MODEL,TRAN | sed 's/^/  /'

read -r -p "Enter target SD device (e.g. /dev/sdb): " DEV
if [[ -z "${DEV}" || ! -b "${DEV}" ]]; then
  echo "Invalid device: ${DEV}"
  exit 1
fi

read -r -p "This will erase ${DEV}. Type ERASE to continue: " CONFIRM
if [[ "${CONFIRM}" != "ERASE" ]]; then
  echo "Aborted."
  exit 1
fi

if ! command -v sudo >/dev/null 2>&1; then
  echo "sudo not available. Manual commands:"
  echo "  sudo wipefs -a ${DEV}"
  echo "  sudo parted -s ${DEV} mklabel msdos"
  echo "  sudo parted -s ${DEV} mkpart primary fat32 1MiB 100%"
  echo "  sudo mkfs.fat -F 32 ${DEV}1"
  echo "  mkdir -p /tmp/mistable-sd && sudo mount ${DEV}1 /tmp/mistable-sd"
  echo "  sudo cp -av assets/sdroot/* /tmp/mistable-sd/ && sync && sudo umount /tmp/mistable-sd"
  exit 0
fi

if ! command -v mkfs.fat >/dev/null 2>&1; then
  echo "mkfs.fat not found. Install: sudo apt-get install dosfstools"
  exit 1
fi

sudo wipefs -a "${DEV}"
sudo parted -s "${DEV}" mklabel msdos
sudo parted -s "${DEV}" mkpart primary fat32 1MiB 100%
PART="${DEV}1"
sudo mkfs.fat -F 32 "${PART}"

MNT="/tmp/mistable-sd"
mkdir -p "${MNT}"
sudo mount "${PART}" "${MNT}"
sudo cp -av assets/sdroot/* "${MNT}/"
sync
sudo umount "${MNT}"

echo "SD prepared successfully."
