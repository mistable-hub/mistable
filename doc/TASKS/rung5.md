# Task Packet: rung5

Status: Draft  
Role: Verification-only developer directive

---

## 1. Purpose

Create the formal Rung 5 verification record for the existing deterministic simulation spine.

This task exists to record what the current implementation baseline actually proves under the new Mistable document-control system.

After this task is complete, the repository should contain:

```text
doc/VERIFICATION/rung5.md
```

That verification record must capture:

```text
current branch
current HEAD
working tree status
commands run
command results
generated artifact information
golden hash comparison
what is proven
what is explicitly not proven
known blockers
next safe candidate
```

This is a verification-only task.

It must not design, implement, refactor, migrate, or expand the system.

---

## 2. Authority

Read and follow:

```text
AGENTS.md
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/task_template.md
doc/VERIFICATION/document_control_stack_baseline.md
```

Task-specific authority:

```text
doc/bringup_ladder.md
    Rung 5: Existing Simulation Spine Verification Record

doc/source_of_truth.md
    Current implementation baseline and current known smoke verification path

doc/TASKS/task_template.md
    Required task packet shape
```

This task packet narrows the work for this task only.

It must not redefine Mistable architecture, roadmap direction, bringup order, source-of-truth mapping, or agent workflow procedure.

If this task conflicts with higher-authority documents, stop and report the conflict.

---

## 3. Bringup Ladder Position

This task corresponds to:

```text
Rung 5: Existing Simulation Spine Verification Record
```

From:

```text
doc/bringup_ladder.md
```

This task may perform only the work needed to verify and record the existing deterministic simulation spine.

Do not start future-rung work.

Do not use this task to repair unrelated historical task drift.

Do not use this task to begin repository structure migration.

---

## 4. Mode

This task is a:

```text
verification
```

The agent must follow verification-mode rules in:

```text
doc/process/agent_workflow.md
```

The agent must also follow review expectations in:

```text
doc/process/code_review.md
```

Do not mix modes unless explicitly authorized.

This task may run verification commands and create the verification record.

This task must not perform implementation work.

---

## 5. Starting Branch

Use the branch named by the invoking prompt.

Do not create, switch, merge, rebase, or delete branches unless the invoking prompt explicitly instructs you to do so.

Run first:

```bash
git status --short
git rev-parse --abbrev-ref HEAD
git rev-parse HEAD
```

If the working tree is dirty before starting, stop and report the existing changes unless the invoking prompt explicitly says to continue from a dirty tree.

---

## 6. Required Initial Review

Before making changes, read the required authority documents and inspect the current files relevant to this task.

At minimum, confirm:

```text
active branch
current HEAD
working tree status
required authority files exist
doc/VERIFICATION/ exists or may be created
current verification commands are available
current golden hash file exists
protected files are not being edited
```

Do not rely on prior chat history as authority.

Do not rely on agent memory as authority.

---

## 7. Allowed Files

This task may create or edit only:

```text
doc/VERIFICATION/rung5.md
```

The task may create the directory if needed:

```text
doc/VERIFICATION/
```

Do not edit any other file.

In particular, do not edit `doc/source_of_truth.md` in this task.

If the verification result appears to require a source-of-truth refresh, report that as a next safe candidate instead of editing it here.

---

## 8. Protected Files

Do not edit these files:

```text
AGENTS.md
CLAUDE.md
README.md
Makefile
container/Dockerfile
dev
scripts/
rtl/
sim/
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/source_of_truth.md
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/task_template.md
doc/TASKS/000_phase0_minimal_spine.md
doc/TASKS/001_container_first_runner.md
doc/TASKS/002_phase1_rp2350_pizero_appliance.md
doc/multi_core_structure.md
doc/core_lift_sim_contract.md
doc/VERIFICATION/document_control_stack_baseline.md
```

If a protected file appears to require modification, stop and report the reason.

---

## 9. Forbidden Scope

Do not add, edit, or implement:

```text
architecture redesign
board interface definitions
virtual board behavior
monitor or debugger behavior
service-link behavior
RTL changes
simulation code changes
Makefile changes
Docker changes
script changes
golden hash updates
historical task reconciliation
repository structure migration
CORE/ECOSYSTEM/BOARD tuple support
NES or other real core lift work
RP2350 or physical-board work
Keystone86 work
README refresh
source-of-truth refresh
new framework abstractions
new build systems
new dependencies
```

This task must not become a general cleanup pass.

---

## 10. Required Work

Implement only the following:

```text
create doc/VERIFICATION/rung5.md
record the starting branch
record the starting HEAD
record the starting working tree status
run the current verification commands
capture command results
record generated artifact information
record golden hash comparison
record what the existing simulation spine proves
record what the existing simulation spine does not prove
record any blockers or failures
record the next safe candidate
```

The verification record must distinguish:

```text
implemented
verified
not claimed
blocked
```

The verification record must be factual.

Do not infer unproven behavior.

Do not describe future work as completed.

---

## 11. Required Non-Claims

This task must not claim:

```text
full virtual board behavior
working monitor/debugger behavior
bounded service/event transport
FPGA interaction
MCU equivalence
service-link transport
CORE/ECOSYSTEM/BOARD migration completion
repository migration into frozen multi-core structure
real upstream core support
NES compatibility
physical-board readiness
RP2350 appliance readiness
Keystone86 PC readiness
multi-ecosystem support
multi-board support
historical task reconciliation
```

The verification record, final report, and any commit message must preserve these non-claims.

---

## 12. Acceptance Commands

Run the following commands from the repository root.

First, capture repository state:

```bash
git status --short
git rev-parse --abbrev-ref HEAD
git rev-parse HEAD
```

Then run the current smoke verification path:

```bash
./scripts/sanity.sh
./scripts/test.sh
```

If the project’s current expected workflow requires entering the trusted container first, run these commands inside the container and record that context in the verification record.

If a command cannot be run, report why.

If a command fails, do not modify implementation files to fix it.

Because this is verification-only, failed commands should be recorded as verification blockers unless the failure is caused solely by missing local tooling or environment setup.

Do not update the golden hash.

Do not run:

```bash
make golden
UPDATE_GOLDEN=1 ./scripts/test.sh
```

unless a future task explicitly authorizes golden update work.

---

## 13. Verification Record Requirements

The file:

```text
doc/VERIFICATION/rung5.md
```

must include sections for:

```text
Purpose
Authority
Repository State
Commands Run
Command Results
Generated Artifact
Golden Hash Comparison
What This Proves
What This Does Not Prove
Known Blockers
Next Safe Candidate
Final Status
```

The generated artifact section must identify, if available:

```text
artifact path
artifact type
whether it exists after the test
observed hash
expected hash source
whether observed hash matched expected hash
```

The final status must be one of:

```text
Verified
Blocked
Failed
Partial
```

Use `Verified` only if the required commands pass and the golden hash comparison succeeds.

---

## 14. Review Requirements

Before reporting completion, inspect the final diff.

Run:

```bash
git status --short
git diff --stat
git diff --check
```

Confirm:

```text
only doc/VERIFICATION/rung5.md changed
no protected files were modified
no source files were modified
no golden hash was updated
no generated artifact was staged or committed
non-claims were preserved
verification claims match command evidence
```

If any generated files appear in the working tree, report them.

Do not add generated artifacts unless explicitly authorized.

---

## 15. Commit Rules

Do not commit unless the invoking prompt explicitly requests a commit.

If committing is requested, commit only after:

```text
the verification record exists
required commands were run or blockers were recorded
the final diff was reviewed
only allowed files were changed
```

Suggested commit message:

```text
docs: record rung5 simulation spine verification
```

Do not push unless explicitly instructed.

---

## 16. Stop Conditions

Stop and report instead of guessing if:

```text
required authority files are missing
the active task conflicts with higher-authority documents
the working tree is dirty before starting and continuation was not authorized
the task requires files outside the allowed list
the task requires protected-file edits not explicitly authorized
the task requires implementation changes
the task requires architecture changes
the task requires golden hash updates
the verification commands cannot be identified
acceptance cannot be proven
the branch or HEAD cannot be identified
```

Stopping and reporting is preferred over inventing architecture.

---

## 17. Required Final Report

At the end of the task, report:

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

The final report must be factual.

Do not overclaim.

Do not describe future work as completed.

---

## 18. Success Definition

This task is successful only if:

```text
only doc/VERIFICATION/rung5.md was created or edited
protected files were not modified
RTL, sim code, Makefile, Docker files, and scripts were not modified
required verification commands were run or blockers were recorded
generated artifact and golden hash comparison were recorded
the verification record clearly states what is proven
the verification record clearly states what is not proven
non-claims were preserved
final report was provided in the required format
```

---

## 19. One-Sentence Summary

This task creates the Rung 5 verification record for the existing deterministic simulation spine; it verifies and records the current baseline only, without changing implementation or starting future-rung work.
