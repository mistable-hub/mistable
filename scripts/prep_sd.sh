#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR=$(cd "$(dirname "$0")/.." && pwd)
SDROOT="${ROOT_DIR}/assets/sdroot"

if [[ "$(uname -s)" != "Linux" ]]; then
  echo "This script supports Linux only."
  exit 1
fi

if [[ ! -d "${SDROOT}" ]]; then
  echo "assets/sdroot missing. Run tools/make_splash.py and tools/make_sd_image.py" >&2
  exit 1
fi

if ! command -v lsblk >/dev/null 2>&1; then
  echo "lsblk not found. Install util-linux." >&2
  exit 1
fi

if ! command -v mkfs.fat >/dev/null 2>&1; then
  echo "mkfs.fat not found. Install with: sudo apt-get install dosfstools" >&2
fi

lsblk -o NAME,SIZE,MODEL,TRAN,RM,MOUNTPOINT

echo "Enter the device name to format (example: sdb). Leave blank to cancel."
read -r DEV
if [[ -z "${DEV}" ]]; then
  echo "Cancelled."
  exit 0
fi

DEV_PATH="/dev/${DEV}"
if [[ ! -b "${DEV_PATH}" ]]; then
  echo "Invalid block device: ${DEV_PATH}" >&2
  exit 1
fi

echo "About to format ${DEV_PATH} as FAT32 and copy SD root contents."
read -r -p "Type YES to continue: " CONFIRM
if [[ "${CONFIRM}" != "YES" ]]; then
  echo "Cancelled."
  exit 1
fi

if command -v sudo >/dev/null 2>&1; then
  sudo mkfs.fat -F 32 "${DEV_PATH}"
  TMP_MNT=$(mktemp -d)
  sudo mount "${DEV_PATH}" "${TMP_MNT}"
  sudo cp -v "${SDROOT}"/* "${TMP_MNT}/"
  sync
  sudo umount "${TMP_MNT}"
  rmdir "${TMP_MNT}"
  echo "SD card prepared."
else
  echo "sudo not available. Run these commands manually:"
  echo "mkfs.fat -F 32 ${DEV_PATH}"
  echo "mount ${DEV_PATH} /mnt"
  echo "cp ${SDROOT}/* /mnt/"
  echo "umount /mnt"
fi
