#!/usr/bin/env bash
set -euo pipefail

./scripts/build.sh

if [[ ! -s build/mistable_phase1.uf2 ]]; then
  echo "ERROR: build/mistable_phase1.uf2 missing or empty"
  exit 1
fi

echo "PASS: build/mistable_phase1.uf2 generated"
