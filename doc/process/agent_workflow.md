# Mistable Agent Workflow

Status: Draft v0.1  
Role: Agent session procedure

---

## 1. Purpose

This document defines how ChatGPT, Claude Code, Codex, or similar AI agents operate in the Mistable repository.

It is downstream from:

```text
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
```

The master design statement defines what Mistable is and must remain.

The roadmap defines where Mistable goes over time.

The bringup ladder defines what order work happens in.

The source-of-truth map describes current repo reality.

This workflow defines how agent sessions are conducted.

It does not define:

```text
roadmap phases
bringup rungs
source-of-truth mapping
active implementation scope
verification records
```

Those responsibilities belong to their own documents.

---

## 2. Core Agent Rule

Coding agents are contributors, not architects.

They execute committed developer directives.

They must not infer project direction from chat history, prior sessions, unstated intent, tool availability, or apparent next steps.

Repo files and Git history are authority.

Agent memory is not authority.

Tool availability is not permission.

---

## 3. Authority Reading Order

At the start of an agent session, the agent must identify the session mode and read only the authority required for that mode.

The normal authority order is:

```text
AGENTS.md
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
active doc/TASKS/<active_rung>.md, when applicable
doc/process/agent_workflow.md
doc/process/code_review.md, for review sessions
doc/VERIFICATION/<rung>.md, when verifying or reviewing prior claims
```

If an active task/rung file is provided, it controls current implementation scope.

If no active task/rung file is provided, the agent must not perform implementation work.

If documents conflict, stop and report the conflict.

Do not silently reinterpret authority documents.

---

## 4. Session Modes

Every agent session must operate in one explicit mode.

The allowed modes are:

```text
planning
implementation
review
verification
handoff
```

A session must not mix modes unless explicitly authorized.

---

## 5. Planning Mode

Planning mode creates or revises planning documents, future task/rung directives, or process documents.

Planning mode may be used by ChatGPT or another reasoning system to help design the next rung from existing authority documents.

Planning mode may create or update documents such as:

```text
doc/ROADMAP.md
doc/bringup_ladder.md
doc/TASKS/<future_rung>.md
doc/process/*.md
doc/source_of_truth.md
```

only when explicitly authorized.

Planning mode must not implement source-code behavior unless the active prompt explicitly changes the session mode and authorizes implementation.

Planning mode must not treat a proposed future task as active implementation authority.

---

## 6. Implementation Mode

Implementation mode changes repository files to satisfy an active task/rung directive.

Implementation mode requires an explicitly named active task/rung file under:

```text
doc/TASKS/
```

The active task/rung file must define:

```text
purpose
allowed files
protected files
forbidden scope
required work
acceptance commands
stop conditions
required final report
explicit non-claims
```

Before editing, the agent must classify the work as:

```text
required blocker
required acceptance cleanup
out of scope
```

Only required blockers and required acceptance cleanup may be implemented.

Out-of-scope work must not be implemented, even if it appears useful.

If required scope is unclear, stop and report the ambiguity.

---

## 7. Classification Before Editing

Before editing files in implementation mode, the agent must provide or internally establish a classification of intended changes.

The classification must distinguish:

```text
required blocker
    Work required for the active task to pass its stated acceptance criteria.

required acceptance cleanup
    Small cleanup required to make the accepted result coherent, documented, or runnable.

out of scope
    Work that may be useful later but is not authorized by the active task.
```

The agent must not broaden the active task by inference.

The agent must not begin future-rung work.

The agent must not modify protected files unless the active task explicitly authorizes it.

---

## 8. Review Mode

Review mode inspects current changes or a proposed diff.

Review mode is read-only unless explicitly authorized otherwise.

In review mode, the agent must not:

```text
edit files
generate patches for immediate application
commit
push
start implementation
broaden the task
```

Review mode should check:

```text
scope alignment
protected file changes
acceptance-command evidence
non-claims
style and maintainability
known blockers
pre-commit concerns
```

Detailed review procedure belongs in:

```text
doc/process/code_review.md
```

---

## 9. Verification Mode

Verification mode records or checks what actually passed.

Verification mode may inspect:

```text
commands run
test output
generated artifacts
commit hash
working tree status
claimed behavior
explicit non-claims
```

Verification mode must distinguish:

```text
implemented
verified
accepted
not claimed
```

A verification record must not overclaim.

A rung is valid only to the extent that its recorded verification remains true.

Formal verification records belong under:

```text
doc/VERIFICATION/
```

---

## 10. Handoff Mode

Handoff mode prepares enough state for a future agent or human to continue safely.

A handoff must identify:

```text
what was attempted
what changed
what commands were run
what passed
what failed
what remains incomplete
what must be verified before proceeding
current branch
current HEAD
working tree status
known blockers
next safe candidate
```

A new session must not rely on previous chat memory.

A new session must recover state from:

```text
committed files
Git status
Git history
active task/rung files
verification records
handoff artifacts, when present
```

---

## 11. Structured Reporting

Agent reports must be structured.

At minimum, implementation and handoff reports should include:

```text
Branch:
HEAD:
Working tree status:
Files changed:
Commands run:
Pass/fail result:
Implemented scope:
Explicit non-claims:
Blockers or concerns:
Next safe candidate:
```

Review reports should include:

```text
Scope result:
Protected-file result:
Acceptance evidence:
Issues found:
Pre-commit concerns:
Out-of-scope changes:
Recommendation:
```

Do not treat an unstructured narrative summary as sufficient proof of completion.

---

## 12. Tool and Capability Boundaries

Agent capability must be controlled by task and process authority.

A coding agent with broad tool access is not automatically authorized to use that access.

Tool availability is not permission.

The right to perform any of the following must be authorized by AGENTS.md, this workflow, the review process, or the active task/rung file:

```text
read broad repo context
edit files
run shell commands
run tests
create commits
push branches
modify protected files
delete files
rewrite history
change dependencies
change toolchain behavior
perform review-only work
```

If a task is review-only, the agent must not edit files.

If a task does not authorize commits or pushes, the agent must not commit or push.

If a task does not authorize protected-file edits, the agent must stop and report the need rather than editing them.

---

## 13. One Active Implementation Agent Policy

Mistable assumes one active implementation agent per branch and active rung unless explicitly authorized otherwise.

Do not run multiple coding agents against the same branch/rung at the same time unless the active task or human project owner explicitly defines how conflicts will be avoided.

Parallel reasoning or review is allowed only when it does not create competing uncoordinated edits.

If multiple agents produce conflicting recommendations, the conflict must be resolved in written repo authority before implementation proceeds.

---

## 14. Context Budget Rule

Agent context is expensive.

Implementation sessions should read only the documents and files required for the active task.

Do not perform broad repository scans, full architecture rereads, or unrelated source inspection unless the active task explicitly requires it or a blocker cannot be understood without it.

If more context appears necessary, stop and report what file, decision, or authority is missing instead of expanding scope silently.

Planning and review sessions may read broader context when explicitly requested.

---

## 15. Historical Task Handling

Historical task files under:

```text
doc/TASKS/
```

may predate the current master design statement, roadmap, and bringup ladder.

Historical tasks are not automatically active.

A historical task becomes active only when:

```text
it is reviewed against current authority documents
it is updated or replaced as needed
a human project owner explicitly names it as the active task/rung
```

Out-of-sequence historical tasks should be deferred, not executed by accident.

---

## 16. Conflict and Stop Conditions

An agent must stop and report instead of guessing if:

```text
authority documents conflict
the active task is missing
the active task does not authorize required edits
required files are missing
protected files would need modification without authorization
acceptance cannot be proven
the same failure repeats after the allowed number of attempts
the working tree contains unexpected unrelated changes
the requested work would skip a required rung
the requested work would violate the master design statement
```

Stopping and reporting is preferred over inventing architecture.

---

## 17. Relationship to Active Tasks

This workflow does not select the active task.

A task becomes active only when a human project owner or active prompt names the task/rung file under:

```text
doc/TASKS/
```

The active task/rung file controls current implementation scope.

This workflow controls how the agent behaves while executing, reviewing, verifying, or handing off that work.

---

## 18. One-Sentence Summary

Mistable agents operate as bounded developer contributors: they read written authority, classify before editing, execute only the active task, report in structured form, preserve handoff state, and stop rather than inventing architecture.
