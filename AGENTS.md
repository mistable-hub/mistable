# AGENTS.md — mistable execution rules

## Purpose
This file defines the standing rules for any execution agent operating on this
repository (e.g., Codex). These rules are stable and apply across all tasks
unless explicitly superseded by a committed task file.

Current phase: Phase 0 — Minimal Spine.

The goal of Phase 0 is to establish a deterministic, runnable simulation spine
that produces a real artifact, with the smallest possible amount of structure.

---

## Authority Model
- The repository is the single source of truth.
- Task definitions live in `doc/TASKS/`.
- Execution agents must implement tasks exactly as written.
- Do not reinterpret, extend, or “improve” requirements.

If a requirement is not written in a committed file, it does not exist.

---

## Allowed Edits (Phase 0)
Execution agents may edit or create files only in the following locations:
- `rtl/`
- `sim/`
- `scripts/`
- `container/`
- root-level `Makefile`
- root-level `.gitignore`
- root-level `README.md`
- `doc/TASKS/`

No other paths may be modified.

---

## Forbidden Actions (Phase 0)
Execution agents must NOT:
- introduce new build systems or frameworks (FuseSoC, CMake, Bazel, Meson, etc.)
- add CI pipelines or CI configuration
- add synthesis or P&R toolchains (yosys, nextpnr, vendor tools)
- add GUI, windowing, or SDL dependencies
- introduce core catalogs, package managers, or dependency systems
- refactor unrelated code
- change scope beyond the active task

If a task requires any of the above, it must say so explicitly.

---

## Definition of Done
A task is considered complete only when all of the following are true:
- `./scripts/test.sh` exits with status code 0
- the expected output artifact exists (as defined by the task)
- no forbidden actions were taken

Partial completion is not completion.

---

## Change Hygiene
- Make the smallest change necessary to satisfy the task.
- Prefer clarity and directness over cleverness.
- Do not introduce abstractions unless the task explicitly requires them.
- Do not “future-proof” or generalize beyond current needs.

---

## Ambiguity Rule
If any instruction is unclear, contradictory, or incomplete:
- STOP.
- Do not invent behavior.
- Do not guess intent.
- Surface the ambiguity instead of proceeding.

Silently filling gaps is considered a failure.

---

## Persistence
This file is intended to be long-lived and rarely changed.
Temporary or task-specific instructions belong in `doc/TASKS/*.md`, not here.
