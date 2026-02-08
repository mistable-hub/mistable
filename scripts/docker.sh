#!/usr/bin/env bash
set -euo pipefail

if [[ $# -eq 0 ]]; then
  echo "Usage: $0 <command...>" >&2
  exit 1
fi

script_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo_root="$script_dir"
while [[ "$repo_root" != "/" && ! -f "$repo_root/AGENTS.md" ]]; do
  repo_root=$(dirname -- "$repo_root")
done
if [[ ! -f "$repo_root/AGENTS.md" ]]; then
  echo "ERROR: AGENTS.md not found" >&2
  exit 1
fi

if ! docker image inspect mistable-dev >/dev/null 2>&1; then
  (cd "$repo_root" && docker build -t mistable-dev -f container/Dockerfile .)
fi

docker_args=(run --rm)
if [[ -t 1 ]]; then
  docker_args+=(-it)
fi
docker_args+=(-v "$repo_root:/work" -w /work)

cmd=$(printf '%q ' "$@")
cmd=${cmd% }

user_args=(-u "$(id -u):$(id -g)")

if docker "${docker_args[@]}" "${user_args[@]}" mistable-dev bash -lc "true" >/dev/null 2>&1; then
  docker "${docker_args[@]}" "${user_args[@]}" mistable-dev bash -lc "$cmd"
  exit $?
fi

echo "WARNING: user mapping failed; running as container default user" >&2
docker "${docker_args[@]}" mistable-dev bash -lc "$cmd"
exit $?
