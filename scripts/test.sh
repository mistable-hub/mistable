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

echo "[test] cleaning previous build output"
rm -rf build
mkdir -p build

echo "[test] building simulation"
make sim

echo "[test] running simulation"
./build/vobj/sim

if [[ ! -f build/frame.ppm ]]; then
  echo "[test] ERROR: build/frame.ppm was not generated" >&2
  exit 1
fi

echo "[test] PASS: build/frame.ppm generated"
