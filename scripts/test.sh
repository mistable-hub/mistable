#!/usr/bin/env bash
set -euo pipefail

./scripts/build.sh

if [[ ! -s build/mistable_phase1.uf2 ]]; then
  echo "ERROR: build/mistable_phase1.uf2 missing"
  exit 1
fi

if [[ ! -s build/mistable_phase1.elf ]]; then
  echo "ERROR: build/mistable_phase1.elf missing"
  exit 1
fi

echo "PASS: Phase 1 artifacts generated"
