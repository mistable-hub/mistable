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

host_uid="$(id -u)"
host_gid="$(id -g)"
host_user="${USER:-devuser}"
host_group="$(id -gn 2>/dev/null || echo devgroup)"
host_home="${HOME:-/tmp}"

tmp_dir="$(mktemp -d)"
trap 'rm -rf "$tmp_dir"' EXIT

cat > "$tmp_dir/passwd" <<EOPASSWD
root:x:0:0:root:/root:/bin/bash
${host_user}:x:${host_uid}:${host_gid}:${host_user}:${host_home}:/bin/bash
EOPASSWD

cat > "$tmp_dir/group" <<EOGROUP
root:x:0:
${host_group}:x:${host_gid}:
EOGROUP

docker_args=(run --rm)

if [[ -t 0 && -t 1 ]]; then
  docker_args+=(-it)
fi

docker_args+=(
  -u "${host_uid}:${host_gid}"
  -e USER="${host_user}"
  -e HOME="${host_home}"
  -e TERM="${TERM:-xterm-256color}"
  -v "$repo_root:/work"
  -v "$tmp_dir/passwd:/etc/passwd:ro"
  -v "$tmp_dir/group:/etc/group:ro"
  -w /work
)

# Mount host ~/.claude config if it exists (for Claude Code authentication)
if [[ -d "$host_home/.claude" ]]; then
  docker_args+=(-v "$host_home/.claude:$host_home/.claude")
fi

# Pass ANTHROPIC_API_KEY through if set on host
if [[ -n "${ANTHROPIC_API_KEY:-}" ]]; then
  docker_args+=(-e ANTHROPIC_API_KEY="${ANTHROPIC_API_KEY}")
fi

if [[ "$#" -eq 1 && "$1" == "bash" ]]; then
  exec docker "${docker_args[@]}" "$image_name" bash --rcfile /work/scripts/bashrc -i
fi

cmd=$(printf '%q ' "$@")
cmd=${cmd% }

exec docker "${docker_args[@]}" "$image_name" bash --rcfile /work/scripts/bashrc -i -c "$cmd"
