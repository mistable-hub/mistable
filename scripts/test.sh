#!/usr/bin/env bash
set -euo pipefail

script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo_root="$script_dir"
while [[ "$repo_root" != "/" && ! -f "$repo_root/AGENTS.md" ]]; do
  repo_root=$(dirname -- "$repo_root")
done

if [[ ! -f "$repo_root/AGENTS.md" ]]; then
  echo "[test] ERROR: AGENTS.md not found" >&2
  exit 1
fi

cd "$repo_root"

golden_hash_file="sim/frame.ppm.sha256"
artifact="build/frame.ppm"

echo "[test] cleaning previous build output"
rm -rf build
mkdir -p build

echo "[test] building simulation"
make sim

echo "[test] running simulation"
./build/vobj/sim

if [[ ! -f "$artifact" ]]; then
  echo "[test] ERROR: $artifact was not generated" >&2
  exit 1
fi

actual_hash="$(sha256sum "$artifact" | awk '{print $1}')"
echo "[test] artifact sha256: $actual_hash"

if [[ "${UPDATE_GOLDEN:-0}" == "1" ]]; then
  echo "$actual_hash" > "$golden_hash_file"
  echo "[test] UPDATED golden hash: $golden_hash_file"
  exit 0
fi

if [[ ! -f "$golden_hash_file" ]]; then
  echo "[test] ERROR: golden hash file missing: $golden_hash_file" >&2
  echo "[test] Hint: run UPDATE_GOLDEN=1 ./scripts/test.sh to create it intentionally." >&2
  exit 1
fi

expected_hash="$(tr -d '[:space:]' < "$golden_hash_file")"

if [[ "$actual_hash" != "$expected_hash" ]]; then
  echo "[test] ERROR: artifact hash mismatch" >&2
  echo "[test] expected: $expected_hash" >&2
  echo "[test] actual:   $actual_hash" >&2
  echo "[test] If this change is intentional, run:" >&2
  echo "[test]   UPDATE_GOLDEN=1 ./scripts/test.sh" >&2
  exit 1
fi

echo "[test] PASS: $artifact generated and matches golden hash"
