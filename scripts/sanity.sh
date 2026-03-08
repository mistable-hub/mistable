#!/usr/bin/env bash
set -euo pipefail

fail() {
  echo "[sanity] FAIL: $1" >&2
  exit 1
}

pass() {
  echo "[sanity] PASS: $1"
}

script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo_root="$script_dir"
while [[ "$repo_root" != "/" && ! -f "$repo_root/AGENTS.md" ]]; do
  repo_root=$(dirname -- "$repo_root")
done

[[ -f "$repo_root/AGENTS.md" ]] || fail "AGENTS.md not found; cannot locate repo root"

cd "$repo_root"

echo "------------------------------------------------------------"
echo "0) Environment"
echo "------------------------------------------------------------"
echo "PWD: $(pwd)"
echo "UID:GID: $(id -u):$(id -g)"
echo "USER: ${USER:-unknown}"

[[ "$(pwd)" == "/work" ]] || fail "expected working directory /work inside container"

echo
echo "------------------------------------------------------------"
echo "1) Required tools"
echo "------------------------------------------------------------"

command -v bash >/dev/null 2>&1 || fail "bash not found"
command -v git >/dev/null 2>&1 || fail "git not found"
command -v make >/dev/null 2>&1 || fail "make not found"
command -v verilator >/dev/null 2>&1 || fail "verilator not found"

echo "bash:      $(bash --version | head -n 1)"
echo "git:       $(git --version)"
echo "make:      $(make --version | head -n 1)"
echo "verilator: $(verilator --version)"

pass "required tools present"

echo
echo "------------------------------------------------------------"
echo "2) Repo contract"
echo "------------------------------------------------------------"

[[ -f "./container/Dockerfile" ]] || fail "container/Dockerfile missing"
[[ -f "./scripts/docker.sh" ]] || fail "scripts/docker.sh missing"
[[ -f "./scripts/test.sh" ]] || fail "scripts/test.sh missing"
[[ -f "./Makefile" ]] || fail "Makefile missing"
[[ -f "./README.md" ]] || fail "README.md missing"
[[ -f "./AGENTS.md" ]] || fail "AGENTS.md missing"
[[ -f "./rtl/mistable_top.sv" ]] || fail "rtl/mistable_top.sv missing"
[[ -f "./sim/tb.cpp" ]] || fail "sim/tb.cpp missing"

pass "repo contract present"

echo
echo "------------------------------------------------------------"
echo "3) Write access"
echo "------------------------------------------------------------"

mkdir -p build
touch build/.sanity_write_test || fail "cannot write to build/"
rm -f build/.sanity_write_test

pass "write access OK"

echo
echo "------------------------------------------------------------"
echo "4) Git state"
echo "------------------------------------------------------------"

git rev-parse --is-inside-work-tree >/dev/null 2>&1 || fail "not inside a git work tree"
echo "branch: $(git rev-parse --abbrev-ref HEAD)"
pass "git repo detected"

echo
echo "------------------------------------------------------------"
echo "5) Verification"
echo "------------------------------------------------------------"

./scripts/test.sh || fail "scripts/test.sh failed"

[[ -f "./build/frame.ppm" ]] || fail "build/frame.ppm missing after test"

pass "verification passed"

echo
echo "[sanity] ALL CHECKS PASSED"
