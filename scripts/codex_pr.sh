#!/usr/bin/env bash
set -euo pipefail

TASK="${1:-}"
if [[ -z "$TASK" ]]; then
  echo "usage: $0 <task-id-like-002>" >&2
  exit 2
fi

# Require clean working tree
if [[ -n "$(git status --porcelain)" ]]; then
  echo "ERROR: working tree not clean. Commit or stash first." >&2
  git status --porcelain
  exit 1
fi

# Find the task file
TASK_FILE="$(ls -1 doc/TASKS/${TASK}_*.md 2>/dev/null | head -n 1 || true)"
if [[ -z "$TASK_FILE" ]]; then
  echo "ERROR: Could not find doc/TASKS/${TASK}_*.md" >&2
  ls -la doc/TASKS || true
  exit 1
fi

BR="codex/task-${TASK}"
git checkout -b "$BR"

cat <<EOF

========================
Codex PR workflow
========================

Run: codex

Then instruct it (copy/paste this line into Codex):

Execute ${TASK_FILE} exactly. Run ./scripts/test.sh until it exits with status 0. Stop.

EOF

read -rp "Press Enter to launch Codex now... "

codex

echo
echo "Running tests..."
./scripts/test.sh

echo
echo "Committing changes..."
git add -A
git commit -m "TASK-${TASK}: implement"

echo
echo "Pushing branch..."
git push -u origin "$BR"

echo
echo "Opening PR..."
if command -v gh >/dev/null 2>&1; then
  gh pr create \
    --title "TASK-${TASK}: implement" \
    --body "Implements ${TASK_FILE} per AGENTS.md. Tests: ./scripts/test.sh" \
    --base main \
    --head "$BR"
else
  echo "NOTE: 'gh' (GitHub CLI) not found. Create PR in GitHub UI:"
  echo "  https://github.com/<owner>/<repo>/compare/main...${BR}?expand=1"
fi
