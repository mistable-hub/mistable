# Document-Control Stack Baseline

Status: Baseline v0.1  
Role: Documentation-only baseline record

---

## 1. Purpose

This document records that the Mistable document-control stack exists, has consistent roles, and is ready to govern future work.

This is a documentation-only baseline record.

It does not verify implementation behavior.

It does not verify the simulation spine.

It does not run or require implementation commands.

It does not authorize changes to RTL, simulation code, Makefile, Docker, scripts, old task files, or source files.

---

## 2. Scope

This baseline covers only the document-control stack.

In scope:

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

Out of scope:

```text
RTL verification
simulation verification
Makefile behavior
Docker behavior
script behavior
generated artifacts
historical task reconciliation
physical board work
virtual board implementation
monitor implementation
core lift implementation
```

---

## 3. Authority Basis

This record is downstream from the current document-control stack.

The document-control stack establishes the following roles:

```text
AGENTS.md
    Standing rules for coding and review agents.
    Entry point for agent behavior and authority discovery.

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
    Describes current repository reality and known non-claims.

doc/process/agent_workflow.md
    Agent session procedure.
    Defines session modes, authority reading order, classification-before-editing,
    handoff expectations, structured reporting, tool/capability boundaries,
    context budget, and stop conditions.

doc/process/code_review.md
    Review procedure.
    Defines read-only review behavior, dirty-diff review expectations,
    protected-file checks, scope checks, acceptance-evidence checks,
    non-claim checks, generated-artifact checks, pre-commit concern categories,
    review output format, and review stop conditions.

doc/TASKS/task_template.md
    Standard developer-directive shape.
    Defines how future task/rung packets should be written.

doc/multi_core_structure.md
    Frozen repository structure and long-term integration policy.
    Defines the intended framework/core/ecosystem/board/build-control structure.

doc/core_lift_sim_contract.md
    Frozen simulation-first core lift contract.
    Defines how upstream cores are to be lifted into the simulation-first path.
```

---

## 4. Document-Control Stack Result

The document-control stack is considered present for documentation-control purposes.

The stack now contains:

```text
root design identity
roadmap direction
bringup ordering
current repo truth map
agent standing rules
agent workflow procedure
code review procedure
task/rung template
frozen multi-core structure policy
frozen simulation-first core-lift contract
```

This means future work can be governed by written authority instead of chat history, agent memory, or implied intent.

---

## 5. Role Consistency Check

The document-control stack is internally consistent at the role level.

The roles are separated as follows:

```text
Master design statement:
    what Mistable is and must remain

Roadmap:
    where Mistable goes

Bringup ladder:
    what order work happens in

Source of truth:
    what the repo currently contains and currently claims

Agent workflow:
    how agents run sessions

Code review:
    how changes are reviewed

Task template:
    how future active task/rung packets are shaped

AGENTS.md:
    standing entry point and agent rules

Frozen structure policy:
    long-term repository structure and integration boundaries

Core lift contract:
    simulation-first upstream core lift rules
```

No document in this stack is intended to silently replace another document’s role.

If future edits cause role overlap or conflict, the conflict must be resolved explicitly.

---

## 6. What This Baseline Proves

This baseline proves only:

```text
the document-control stack exists
the stack has named roles
the stack has a consistent authority model
future agents have a written entry point
future tasks have a task-packet template
future reviews have a review procedure
future agent sessions have a workflow procedure
future roadmap/ladder work has documented authority boundaries
historical task files are not automatically active authority
implementation work still requires an explicitly named active task/rung
```

---

## 7. What This Baseline Does Not Prove

This baseline does not prove:

```text
the simulation spine passes
make sim works
scripts/test.sh works
make sanity works
Docker works
Verilator is installed
build/frame.ppm is generated
the golden hash matches
the repo has migrated to the frozen multi-core structure
CORE/ECOSYSTEM/BOARD tuple support exists
the virtual board exists
the monitor exists
bounded event/status transport exists
any real core lift exists
NES compatibility exists
physical board support exists
RP2350 appliance readiness exists
Keystone86 PC integration exists
historical task files are reconciled
```

These are intentionally not claimed here.

---

## 8. Rung 5 Boundary

Rung 5 is:

```text
Existing Simulation Spine Verification Record
```

Rung 5 has not started in this baseline.

This document does not satisfy Rung 5.

This document only records that the documentation-control stack is ready to govern future Rung 5 work.

The simulation spine must be verified separately, under a future active task/rung or explicit human instruction.

---

## 9. Historical Task Files

Historical task files under:

```text
doc/TASKS/
```

remain pending reconciliation.

They must not be treated as active authority merely because they exist.

A historical task becomes active only when:

```text
it is reviewed against the current document-control stack
it is updated or replaced as needed
a human project owner explicitly names it as the active task/rung
```

This baseline does not reconcile historical tasks.

---

## 10. Current Next Safe Candidate

The next safe candidate depends on whether the project wants to remain documentation-only or begin implementation-baseline verification.

Documentation-only next candidates:

```text
review document-control stack for consistency
refresh doc/source_of_truth.md if this baseline changes current repo truth
create a future task packet for Rung 5 without executing it
review/reconcile historical task files as documentation-only work
```

Implementation-baseline next candidate:

```text
Rung 5: Existing Simulation Spine Verification Record
```

Rung 5 should not begin until explicitly authorized.

---

## 11. Conflict Rule

If this baseline conflicts with:

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

stop and resolve the conflict explicitly.

Do not silently reinterpret authority documents.

This baseline must not override higher-authority documents.

---

## 12. One-Sentence Summary

The Mistable document-control stack is now present and role-consistent enough to govern future work, but implementation-baseline verification, including Rung 5 simulation-spine verification, has not started.
