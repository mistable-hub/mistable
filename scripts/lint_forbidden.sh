#!/usr/bin/env bash
set -euo pipefail

if grep -REn '#include[[:space:]]*[<"](pthread\.h|unistd\.h|fcntl\.h|termios\.h)[>"]' src; then
  echo "Forbidden desktop header detected"
  exit 1
fi

if grep -REn '#include[[:space:]]*[<"]sys/' src; then
  echo "Forbidden sys/ header detected"
  exit 1
fi

if grep -REn 'pthread_' src; then
  echo "Forbidden pthread symbol detected"
  exit 1
fi

if grep -REn '(malloc\(|free\()' src/video; then
  echo "Forbidden malloc/free in src/video"
  exit 1
fi

echo "lint_forbidden: OK"
