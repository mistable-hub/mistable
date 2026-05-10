# AGENTS.md — Mistable Agent Rules

Status: Baseline v0.2  
Role: Standing rules for coding and review agents

---

## 1. Purpose

This file defines the standing rules for any AI execution, coding, review, or planning agent operating in this repository.

Examples include:

```text
Codex
Claude Code
ChatGPT-assisted coding workflows
other coding agents
```

Agents are contributors, not architects.

Agents execute written repository authority.

Agents must not infer project direction from chat history, prior sessions, tool availability, or unstated intent.

---

## 2. Core Rule

Repo files are authority.

Agent memory is not authority.

Tool availability is not permission.

If a requirement is not written in a committed authority file or active task/rung directive, it does not authorize implementation.

When in doubt, stop and report instead of guessing.

---

## 3. Authority Stack

Agents must treat the following files as the current authority system:

```text
doc/master_design_statement.md
    Root identity.
    Defines what Mistable is and must remain.

doc/ROADMAP.md
    Big-picture development phases.
    Defines where Mistable goes over time.

doc/bringup_ladder.md
    Ordered proof rungs.
    Defines what order work happens in.

doc/source_of_truth.md
    Current repo truth map.
    Defines current repository reality and known non-claims.

doc/process/agent_workflow.md
    Agent session procedure.
    Defines session modes, authority reading order, reporting, handoff, tool boundaries, and stop conditions.

doc/process/code_review.md
    Review procedure.
    Defines read-only review, dirty-diff review, scope checks, protected-file checks, and review output.

doc/TASKS/task_template.md
    Standard developer-directive shape for future task/rung files.

doc/TASKS/<active_rung>.md
    Active developer directive when explicitly named by the human project owner or invoking prompt.
```

Additional frozen architecture and core-lift policy documents:

```text
doc/multi_core_structure.md
    Frozen repository structure and long-term integration policy.

doc/core_lift_sim_contract.md
    Frozen simulation-first upstream core lift contract.
```

If these documents conflict, stop and report the conflict.

Do not silently reinterpret authority documents.

---

## 4. Active Task Requirement

Implementation work requires an explicitly named active task/rung file under:

```text
doc/TASKS/
```

If no active task/rung file is named, agents may review, summarize, or help plan only when explicitly asked.

Agents must not implement future roadmap or bringup-ladder work merely because it appears to be next.

The roadmap and bringup ladder define direction and order.

They do not authorize implementation by themselves.

---

## 5. Session Modes

Agents must operate in one explicit mode:

```text
planning
implementation
review
verification
handoff
```

Follow:

```text
doc/process/agent_workflow.md
```

Do not mix modes unless explicitly authorized.

Review mode is read-only unless explicitly authorized otherwise.

Implementation mode requires an active task/rung file.

---

## 6. Historical Task Files

Existing task files under:

```text
doc/TASKS/
```

may predate the current master-design / roadmap / bringup-ladder system.

Historical task files are not automatically active authority.

A historical task becomes active only when:

```text
it is reviewed against doc/master_design_statement.md
it is reviewed against doc/ROADMAP.md
it is reviewed against doc/bringup_ladder.md
it is updated or replaced as needed
a human project owner explicitly names it as the active task/rung
```

Out-of-sequence historical tasks should be deferred rather than executed by accident.

Physical hardware or appliance work must not bypass the simulation-first and virtual-board-first path unless explicitly authorized by a current task/rung.

---

## 7. Classification Before Editing

Before editing files in implementation mode, classify intended work as:

```text
required blocker
required acceptance cleanup
out of scope
```

Only required blockers and required acceptance cleanup may be implemented.

Out-of-scope work must not be implemented.

Do not broaden the active task by inference.

Do not begin future-rung work.

---

## 8. Protected Authority Files

The following files are protected authority files:

```text
AGENTS.md
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/task_template.md
doc/multi_core_structure.md
doc/core_lift_sim_contract.md
```

Do not edit protected authority files unless the active task or human prompt explicitly authorizes that specific file change.

If a protected authority file appears to require modification, stop and report the reason.

---

## 9. Tool and Capability Boundaries

An agent may have access to tools such as:

```text
file editing
shell commands
tests
git status
git diff
git commit
git push
network access
package installation
```

Access does not imply permission.

Tool use must be authorized by:

```text
this file
doc/process/agent_workflow.md
doc/process/code_review.md
the active task/rung file
the human project owner
```

If a task does not authorize commits, do not commit.

If a task does not authorize pushes, do not push.

If a task is review-only, do not edit files.

If a task does not authorize dependency or toolchain changes, do not change dependencies or toolchains.

---

## 10. Build and Test Discipline

Use visible repository entry points.

The current source-of-truth map identifies current build and test paths.

Do not replace Make with hidden script behavior.

Do not introduce new build systems, dependency managers, frameworks, or toolchains unless the active task explicitly authorizes them.

Compile success alone is not acceptance.

Passing tests alone is not permission to overclaim.

Verification claims must match the evidence.

---

## 11. Non-Claims Discipline

Do not claim behavior that has not been proven.

Common non-claims unless explicitly proven by an active rung and verification record:

```text
full virtual board behavior
working monitor/debugger behavior
FPGA interaction
MCU equivalence
service-link transport
CORE/ECOSYSTEM/BOARD migration completion
real upstream core support
NES compatibility
physical-board readiness
RP2350 appliance readiness
Keystone86 PC readiness
multi-ecosystem support
multi-board support
```

Stubs, placeholders, wrappers, interface names, or TODOs are not features.

A resource exists only when the active rung defines its scope and verification records what passed.

---

## 12. Review Discipline

When asked to review changes, follow:

```text
doc/process/code_review.md
```

Review is read-only unless explicitly authorized otherwise.

A review must check at least:

```text
scope alignment
protected-file changes
acceptance evidence
non-claims
generated artifacts
pre-commit concerns
out-of-scope work
```

Do not turn a review into an implementation pass.

Do not commit during review unless explicitly authorized.

---

## 13. Source-of-Truth Discipline

When repo state changes in a way that affects current file roles, current process documents, current missing documents, current proof status, or current next position, update or flag:

```text
doc/source_of_truth.md
```

Do not allow the source-of-truth map to become silently stale when the task explicitly changes document-system state.

The source-of-truth map describes current repo reality only.

It must not become the roadmap, bringup ladder, task template, or workflow procedure.

---

## 14. Context Budget

Agent context is expensive.

Read only the files required for the current mode and active task.

Do not perform broad repository scans unless explicitly requested or necessary to resolve a blocker.

If more context is needed, report what is missing and why.

---

## 15. Stop Conditions

Stop and report instead of guessing if:

```text
authority documents conflict
the active task is missing for implementation work
required authority files are missing
the requested work skips a required rung
the requested work violates doc/master_design_statement.md
the working tree contains unexpected unrelated changes
the task requires files outside the allowed list
the task requires protected-file edits without authorization
acceptance cannot be proven
required commands fail after the allowed attempts
the same error repeats after the allowed fix attempts
the branch or HEAD cannot be identified
the agent would need to invent architecture to proceed
```

Stopping and reporting is preferred over silent improvisation.

---

## 16. Required Final Report

For implementation or handoff work, report:

```text
Branch:
HEAD:
Working tree status:
Files changed:
Commands run:
Pass/fail result:
Implemented scope:
Explicit non-claims:
What was not implemented:
Known blockers:
Next safe candidate:
```

For review work, report using the structure defined in:

```text
doc/process/code_review.md
```

Do not treat an unstructured narrative summary as sufficient proof of completion.

---

## 17. Persistence

This file is intended to be long-lived and rarely changed.

Task-specific instructions belong in:

```text
doc/TASKS/<active_rung>.md
```

Process details belong in:

```text
doc/process/
```

Current repo-state mapping belongs in:

```text
doc/source_of_truth.md
```

Do not duplicate downstream documents here.

This file is the standing entry point for agents, not the whole project spec.

---

## 18. One-Sentence Summary

Mistable agents must operate as bounded contributors: read written authority, use the active task for implementation scope, classify before editing, preserve non-claims, respect tool boundaries, review read-only unless authorized, and stop rather than inventing architecture.
