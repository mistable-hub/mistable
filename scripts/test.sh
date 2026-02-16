#!/usr/bin/env bash
set -euo pipefail

scripts/build.sh

if [[ ! -f build/mistable_phase1.uf2 ]]; then
  echo "ERROR: build/mistable_phase1.uf2 missing"
  exit 1
fi

echo "PASS: build/mistable_phase1.uf2 generated"
