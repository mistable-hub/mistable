# AGENTS.md

This repository uses these documents as controlling instructions:
- `doc/multi_core_structure.md`
- `doc/core_lift_sim_contract.md`

Hard rules:
- Do not redesign repository architecture.
- Follow the frozen structure document.
- For core lifts, follow the lift contract exactly.
- For hard or ambiguous tasks, plan first before editing.
- Prefer small, reviewable commits.
- Keep shared ecosystem and board changes minimal and generic.
- Do not treat compile success as acceptance.

A core-lift task is not complete unless:
- the required retained-boundary decision is explicit
- required local files exist
- a simulation entry point exists for sim-first lifts
- an exact build/run command is provided when possible
- blockers are reported explicitly if the lift cannot legally continue