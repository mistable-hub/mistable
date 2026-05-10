# Mistable Code Review Procedure

Status: Draft v0.1  
Role: Review procedure

---

## 1. Purpose

This document defines how changes are reviewed in the Mistable repository.

It is downstream from:

```text
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
doc/process/agent_workflow.md
```

The master design statement defines what Mistable is and must remain.

The roadmap defines where Mistable goes over time.

The bringup ladder defines what order work happens in.

The source-of-truth map describes current repo reality.

The agent workflow defines how agent sessions operate.

This document defines review procedure only.

It does not define:

```text
roadmap phases
bringup rungs
source-of-truth mapping
task/rung template structure
implementation instructions
active task authorization
verification records
```

Those responsibilities belong to their own documents.

---

## 2. Core Review Rule

Review is read-only unless explicitly authorized otherwise.

A review session must not:

```text
edit files
apply patches
generate replacement files for immediate application
commit
push
delete files
rewrite history
start implementation work
broaden the active task
```

A reviewer may recommend changes.

A reviewer may identify blockers.

A reviewer may classify issues by severity.

A reviewer may propose follow-up tasks.

A reviewer must not perform implementation unless the session is explicitly changed from review mode to implementation mode and an active task/rung authorizes the work.

---

## 3. Review Authority

A review must check changes against the relevant authority documents.

The normal review authority order is:

```text
AGENTS.md
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/<active_rung>.md, when reviewing active task work
doc/VERIFICATION/<rung>.md, when reviewing verification claims
```

If an active task/rung file exists, it controls the authorized implementation scope.

If there is no active task/rung file, the review must not assume that implementation work was authorized.

If documents conflict, stop and report the conflict.

Do not silently reinterpret authority documents.

---

## 4. Dirty-Diff Review

A dirty-diff review inspects uncommitted changes before commit.

The reviewer should inspect:

```text
git status --short
git diff --stat
git diff
git diff --check
```

When relevant, the reviewer may also inspect staged changes:

```text
git diff --cached --stat
git diff --cached
git diff --cached --check
```

A dirty-diff review must answer:

```text
What files changed?
Were the changed files authorized?
Were protected files modified?
Does the diff implement only the active task?
Did future-rung work appear?
Did generated artifacts change?
Did source files change without matching documentation or tests when required?
Did documentation overclaim behavior?
Did verification evidence actually support the claims?
```

A dirty diff must not be considered ready merely because it compiles.

---

## 5. Protected-File Review

Review must identify whether protected or authority files were changed.

Protected files may include, depending on the active task:

```text
AGENTS.md
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
doc/process/
doc/TASKS/
doc/VERIFICATION/
doc/multi_core_structure.md
doc/core_lift_sim_contract.md
```

A protected-file change is acceptable only when the active task or human project owner explicitly authorized it.

If a protected file changed without authorization, the review result must be:

```text
not ready
```

The reviewer must report the protected-file change as a blocker.

---

## 6. Scope Review

A scope review checks whether the changes stayed inside the active task.

The reviewer must classify changed work as:

```text
authorized
required acceptance cleanup
out of scope
unclear
```

Definitions:

```text
authorized
    Directly required by the active task/rung.

required acceptance cleanup
    Small cleanup required for the active task to be coherent, runnable, or reviewable.

out of scope
    Useful or plausible work that is not authorized by the active task/rung.

unclear
    Work whose authorization cannot be determined from the active task and authority documents.
```

Out-of-scope implementation must be reported.

Unclear scope must be reported.

The reviewer must not bless future-rung work merely because it seems useful.

---

## 7. Acceptance-Evidence Review

A review must check whether required acceptance evidence exists.

Acceptance evidence may include:

```text
commands requested by the active task
test output
sanity output
simulation output
generated artifacts
hash comparisons
manual inspection notes
known failure logs
```

The reviewer must distinguish:

```text
not run
run and passed
run and failed
run but evidence missing
not applicable
```

A task is not ready if required acceptance commands were not run, unless the active task explicitly allows documentation-only or status-only completion.

If acceptance cannot be proven, the review must say so.

Do not treat narrative claims as a substitute for command evidence.

---

## 8. Non-Claim Review

A review must check that the change does not claim more than it proves.

The reviewer should look for overclaims in:

```text
README.md
doc/
comments
commit message
final report
verification records
task completion notes
```

Examples of overclaims:

```text
claiming virtual board support when only stubs exist
claiming monitor/debugger behavior when only a shell exists
claiming FPGA interaction when no transport exists
claiming MCU equivalence when only a host script exists
claiming core compatibility from compile-only evidence
claiming physical-board readiness from simulation-only work
claiming Keystone86 readiness from smaller-core scaffolding
```

If the change includes unproven claims, the review must mark them as pre-commit concerns or blockers depending on severity.

---

## 9. Generated Artifact Review

Generated artifacts must be reviewed carefully.

The reviewer must identify whether generated files changed, such as:

```text
build/
generated images
hash files
logs
compiled outputs
temporary files
```

Generated artifacts should not be committed unless the active task explicitly requires them.

Golden or checksum files must not be updated unless the active task explicitly authorizes a golden update.

If a golden file changes, the review must require an explanation of why the behavior change is intended.

---

## 10. Documentation Review

Documentation changes must be checked for role discipline.

A documentation change must not make one document do another document’s job.

Examples:

```text
doc/master_design_statement.md
    must not become roadmap, bringup ladder, or task workflow.

doc/ROADMAP.md
    must not authorize active implementation.

doc/bringup_ladder.md
    must not define exact task file edits or command scripts.

doc/source_of_truth.md
    must describe current repo reality only.

doc/process/agent_workflow.md
    must define agent procedure, not project direction.

doc/process/code_review.md
    must define review procedure, not implementation scope.

doc/TASKS/<active_rung>.md
    must define current authorized scope.

doc/VERIFICATION/<rung>.md
    must record what actually passed, not future plans.
```

If a document silently duplicates, replaces, or redefines another document’s job, the review must report it.

---

## 11. Code Review

Code review should check correctness only within the authorized scope.

The reviewer should check:

```text
minimality
readability
determinism
build/test compatibility
error handling
dependency changes
hidden behavior
hardcoded assumptions
generated-vs-source boundaries
```

The reviewer must not request broad refactors unless the active task authorizes them or the current change cannot be accepted safely without them.

Style concerns should not override scope discipline.

---

## 12. Agent-Workflow Review

When reviewing work performed by an AI coding agent, the reviewer must check whether the agent followed:

```text
doc/process/agent_workflow.md
```

The review should verify:

```text
the session mode was appropriate
implementation had an active task/rung
classification-before-editing was respected when required
tool/capability boundaries were respected
review-only mode stayed read-only
structured reporting was provided
handoff state was preserved when needed
one-active-implementation-agent policy was not violated
```

Agent convenience is not a reason to accept scope drift.

---

## 13. Pre-Commit Concern Categories

A review should classify concerns as:

```text
blocker
    Must be fixed before commit.

pre-commit concern
    Should be fixed before commit unless explicitly deferred.

follow-up
    Valid issue, but not required before this commit.

non-blocking note
    Observation only.

out of scope
    Not part of this task/rung.
```

Examples of blockers:

```text
protected file changed without authorization
acceptance command failed
required acceptance command not run
implementation exceeded active scope
verification overclaims behavior
wrong branch or unknown branch
unexpected unrelated dirty files
authority document conflict
```

Examples of follow-ups:

```text
future cleanup
future refactor
future resource implementation
future task reconciliation
future README expansion
```

---

## 14. Review Output Format

A review report should use this structure:

```text
Review result:
Scope result:
Protected-file result:
Acceptance evidence:
Non-claim result:
Generated artifact result:
Issues found:
Pre-commit concerns:
Out-of-scope changes:
Recommended action:
```

Where possible, include:

```text
Branch:
HEAD:
Working tree status:
Files reviewed:
Commands or evidence reviewed:
```

Recommended actions should be one of:

```text
ready
ready with notes
not ready
blocked
needs clarification
```

Do not bury blockers inside prose.

---

## 15. Review Result Meanings

Review result meanings are:

```text
ready
    Changes appear within scope, required evidence exists, and no blockers were found.

ready with notes
    Changes appear acceptable, but non-blocking follow-ups or observations exist.

not ready
    One or more pre-commit concerns should be fixed before commit.

blocked
    A blocker prevents safe acceptance.

needs clarification
    Required authority, scope, or evidence is unclear.
```

A review may not mark work ready if required evidence is missing.

A review may not mark work ready if known overclaims remain.

A review may not mark work ready if protected files were changed without authorization.

---

## 16. Review Stop Conditions

A reviewer must stop and report instead of guessing if:

```text
authority documents conflict
the active task is missing and implementation scope matters
the diff includes unexpected protected-file changes
the diff includes unrelated work mixed with task work
required acceptance evidence is missing
the branch or HEAD cannot be identified when required
the review requires unavailable files
the review would require implementation to complete
the change appears to skip a required rung
```

Stopping and reporting is preferred over inventing authority.

---

## 17. Relationship to Verification

Review is not the same as verification.

Review answers:

```text
Does this change appear acceptable against scope, authority, and evidence?
```

Verification answers:

```text
What actually passed, at what commit, with what command, and what is proven?
```

Formal verification records belong under:

```text
doc/VERIFICATION/
```

A review may recommend creating or updating a verification record.

A review must not fabricate verification evidence.

---

## 18. Relationship to Active Tasks

This review procedure does not select the active task.

A task becomes active only when a human project owner or active prompt names the task/rung file under:

```text
doc/TASKS/
```

The active task/rung file controls current implementation scope.

This review procedure controls how changes are inspected.

---

## 19. One-Sentence Summary

Mistable review is a read-only gate that checks scope, protected files, acceptance evidence, non-claims, generated artifacts, and pre-commit concerns before work is accepted.
