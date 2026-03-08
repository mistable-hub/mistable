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

image_name="${IMAGE_NAME:-mistable-dev}"

if ! docker image inspect "$image_name" >/dev/null 2>&1; then
  (cd "$repo_root" && docker build -t "$image_name" -f container/Dockerfile .)
fi

docker_args=(run --rm)

if [[ -t 1 ]]; then
  docker_args+=(-it)
fi

docker_args+=(
  -v "$repo_root:/work"
  -w /work
)

cmd=$(printf '%q ' "$@")
cmd=${cmd% }

user_args=(-u "$(id -u):$(id -g)")

if docker "${docker_args[@]}" "${user_args[@]}" "$image_name" bash -lc "true" >/dev/null 2>&1; then
  exec docker "${docker_args[@]}" "${user_args[@]}" "$image_name" bash -lc "$cmd"
fi

echo "WARNING: user mapping failed; running as container default user" >&2
exec docker "${docker_args[@]}" "$image_name" bash -lc "$cmd"
