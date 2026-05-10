# Mistable Source of Truth Map

Status: Draft v0.4  
Role: Current repo truth map

---

## 1. Purpose

This document maps the current repository state so humans and coding agents do not guess which files own which facts.

It is downstream from:

```text
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
```

The master design statement defines what Mistable is and must remain.

The roadmap defines where Mistable goes over time.

The bringup ladder defines what order work happens in.

This source-of-truth map describes current repo reality only.

It does not define:

```text
roadmap phases
bringup order
task/rung template structure
agent workflow procedure
active task authorization
verification results for completed rungs
```

Those responsibilities belong to the appropriate documents in the document system.

---

## 2. Current Document Authority Stack

The current top-level authority files are:

```text
AGENTS.md
    Standing rules for coding and review agents.
    Entry point for agent behavior and authority discovery.

doc/master_design_statement.md
    Root design identity.
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

These files describe the current authority system, project direction, current repo truth, and process structure.

They do not, by themselves, authorize implementation.

Active implementation authority must come from a reconciled task/rung file under:

```text
doc/TASKS/
```

---

## 3. Current Agent Instruction File

The current repository contains:

```text
AGENTS.md
```

Current role:

```text
standing entry point for coding and review agents
```

Current reality:

```text
AGENTS.md has been reconciled with the current document system
AGENTS.md references the master design statement, roadmap, bringup ladder, source-of-truth map, process documents, and task template
AGENTS.md requires active task/rung authorization before implementation work
AGENTS.md treats historical task files as pending reconciliation
AGENTS.md preserves tool/capability boundaries and non-claims discipline
```

Current treatment:

```text
AGENTS.md is the first file coding and review agents should read
AGENTS.md is not the whole project spec
AGENTS.md must not duplicate or replace downstream authority documents
AGENTS.md should remain long-lived and rarely changed
```

Non-claim:

```text
AGENTS.md does not authorize implementation by itself
```

---

## 4. Current Historical Task Files

The current repository contains historical task files under:

```text
doc/TASKS/
```

Current known historical task files:

```text
doc/TASKS/000_phase0_minimal_spine.md
doc/TASKS/001_container_first_runner.md
doc/TASKS/002_phase1_rp2350_pizero_appliance.md
```

Current treatment:

```text
these task files predate the current master-design / roadmap / bringup-ladder system
they may describe completed work, useful historical intent, or out-of-sequence future work
they are pending reconciliation
they are not automatically current active authority
```

A historical task becomes active only when:

```text
it is reviewed against doc/master_design_statement.md
it is reviewed against doc/ROADMAP.md
it is reviewed against doc/bringup_ladder.md
it is updated or replaced as needed
a human project owner explicitly names it as the active task/rung
```

Known concern:

```text
doc/TASKS/002_phase1_rp2350_pizero_appliance.md describes physical RP2350 appliance work
physical appliance work is out of sequence under the current roadmap until the virtual-board path is proven
this task should be deferred or reconciled later, not executed now
```

---

## 5. Current Task Template

The current repository contains:

```text
doc/TASKS/task_template.md
```

Current role:

```text
standard developer-directive shape for future task/rung files
```

Current reality:

```text
task/rung template now exists
future task packets should be derived from this template unless a human project owner explicitly authorizes otherwise
the template defines expected sections for purpose, authority, ladder position, mode, branch rules, allowed files, protected files, forbidden scope, required work, non-claims, acceptance commands, review requirements, commit rules, stop conditions, final report, and success definition
```

Non-claims:

```text
doc/TASKS/task_template.md does not authorize implementation by itself
doc/TASKS/task_template.md does not make historical tasks current
doc/TASKS/task_template.md does not replace active task/rung packets
```

---

## 6. Current Implementation Baseline

The current implementation baseline is the existing deterministic simulation spine.

Current implementation files:

```text
rtl/mistable_top.sv
sim/tb.cpp
sim/frame.ppm.sha256
```

Current roles:

```text
rtl/mistable_top.sv
    Current minimal RTL top.
    Produces deterministic video-like output for the simulation spine.

sim/tb.cpp
    Current C++ simulation harness.
    Drives the RTL simulation and writes the output artifact.

sim/frame.ppm.sha256
    Golden checksum for the current simulation artifact.
    Used by scripts/test.sh to detect unintended output changes.
```

Current generated artifact:

```text
build/frame.ppm
```

Current role of generated artifact:

```text
observable output produced by the current simulation spine
binary PPM image
used as the current deterministic smoke artifact
```

Non-claims:

```text
the current simulation spine is not a full virtual board
the current simulation spine is not a monitor/service-link system
the current simulation spine is not a multi-core framework
the current simulation spine is not a real upstream core lift
the current simulation spine is not physical-board ready
```

---

## 7. Current Build and Control Files

The current visible build/control entry point is:

```text
Makefile
```

Current known Make targets:

```text
make sim
make clean
make shell
make sanity
make golden
```

Current roles:

```text
make sim
    Builds and runs the current Verilator simulation.

make clean
    Removes generated build output.

make shell
    Enters the trusted container shell through ./dev.

make sanity
    Runs ./scripts/sanity.sh.

make golden
    Refreshes the golden smoke hash through UPDATE_GOLDEN=1 ./scripts/test.sh.
```

Current non-claim:

```text
the Makefile does not yet express the future CORE/ECOSYSTEM/BOARD tuple model
```

The tuple model belongs to later structure-migration rungs.

---

## 8. Current Container and Environment Files

The current container and environment files are:

```text
container/Dockerfile
dev
scripts/docker.sh
scripts/bashrc
scripts/sanity.sh
```

Current roles:

```text
container/Dockerfile
    Defines the current development container/tool environment.

dev
    Convenience entry point for entering the trusted container shell.

scripts/docker.sh
    Current Docker runner.
    Builds/uses the mistable-dev image and mounts the repo at /work.

scripts/bashrc
    Shell defaults for interactive container sessions.

scripts/sanity.sh
    Environment and repo sanity gate.
    Checks expected tools, repo contract, write access, git visibility, and simulation health.
```

Current important behavior:

```text
scripts/sanity.sh expects to run inside /work
scripts/sanity.sh requires Verilator and core command-line tools
scripts/sanity.sh checks current Phase 0 repo contract files
```

Current non-claim:

```text
the container workflow does not prove future virtual board behavior
the container workflow does not prove future core-lift behavior
the container workflow does not prove physical-board readiness
```

---

## 9. Current Test and Verification Files

The current test entry point is:

```text
scripts/test.sh
```

Current role:

```text
authoritative current smoke verification script for the existing simulation spine
```

Current behavior:

```text
cleans previous build output
builds the simulation through make sim
runs the simulation
checks that build/frame.ppm exists
computes the artifact SHA-256
compares it against sim/frame.ppm.sha256
prints PASS when the artifact matches the golden hash
```

Current golden-update path:

```text
UPDATE_GOLDEN=1 ./scripts/test.sh
make golden
```

Current verification status:

```text
the repo has a working smoke verification path
the smoke verification path has not yet been recorded under the new doc/VERIFICATION/ system
```

Non-claim:

```text
scripts/test.sh is not yet a formal rung verification record
```

The first formal verification record belongs to a later rung.

---

## 10. Current Documentation Files

Current root/project documentation:

```text
README.md
LICENSE
.gitignore
```

Current roles:

```text
README.md
    Describes the current Phase 0 baseline, container workflow, simulation artifact, and long-term project direction.

LICENSE
    Project license file.

.gitignore
    Ignore rules for generated/local files.
```

Current reality:

```text
README.md still reflects the existing Phase 0 baseline and long-term structure direction
README.md may need later updates as the new document system becomes active
```

Non-claim:

```text
README.md is not the root design authority
README.md is not the bringup ladder
README.md is not the active task authority
```

---

## 11. Current Frozen Architecture Documents

The current frozen architecture/policy documents are:

```text
doc/multi_core_structure.md
doc/core_lift_sim_contract.md
```

Current roles:

```text
doc/multi_core_structure.md
    Frozen long-term repository structure and integration policy.
    Defines the intended layered structure for framework, cores, ecosystems, boards, external upstream cores, and build/control.

doc/core_lift_sim_contract.md
    Frozen simulation-first upstream core lift contract.
    Defines how real upstream cores should be audited, wrapped, integrated, and reviewed for simulation-first use.
```

Current reality:

```text
these documents already exist
the current repo is not yet fully migrated into the structure described by doc/multi_core_structure.md
real core-lift work should not proceed until the required structural rungs are reached
```

Non-claim:

```text
existence of these documents does not mean the repo already implements the final structure
existence of these documents does not mean a real core lift has started
```

---

## 12. Current Process Documents

The current process document state is:

```text
doc/process/agent_workflow.md
    Exists.
    Defines agent session modes, authority reading order, classification-before-editing,
    handoff expectations, structured reporting, tool/capability boundaries,
    one-active-implementation-agent policy, context budget rule, historical task handling,
    and stop conditions.

doc/process/code_review.md
    Exists.
    Defines read-only review behavior, dirty-diff review expectations,
    protected-file checks, scope checks, acceptance-evidence checks,
    non-claim checks, generated-artifact checks, pre-commit concern categories,
    review output format, and review stop conditions.
```

Current reality:

```text
agent workflow procedure now exists in the new document system
code review procedure now exists in the new document system
```

Non-claims:

```text
doc/process/agent_workflow.md does not authorize implementation by itself
doc/process/agent_workflow.md does not replace active task/rung files
doc/process/code_review.md does not authorize implementation by itself
doc/process/code_review.md does not replace active task/rung files
```

---

## 13. Current Missing Planned Documents

The current document system references files that are planned but not yet complete.

Known planned documents include:

```text
doc/VERIFICATION/<rung>.md
```

Current treatment:

```text
formal verification records are expected by the document system
verification records should be created in future rungs
verification records should not be assumed to exist until they are committed
```

Non-claims:

```text
formal verification records do not yet exist under doc/VERIFICATION/
```

---

## 14. What Is Currently Proven

The current repo proves, at most:

```text
there is an existing minimal deterministic simulation spine
the simulation can produce an observable build artifact
the repo has a Docker-oriented development environment
the repo has Make/script entry points for current smoke verification
the repo has a golden hash file for the current frame artifact
the project now has a root design statement, roadmap, bringup ladder, source-of-truth map, and reconciled AGENTS.md
the project now has agent workflow, code review procedure, and task template documents
the project has frozen long-term structure and core-lift policy documents
```

This is the current baseline.

---

## 15. What Is Not Currently Proven

The current repo does not yet prove:

```text
full virtual board behavior
working monitor behavior
bounded service/event transport
FPGA/MCU service-link behavior
CORE/ECOSYSTEM/BOARD tuple implementation
migration into the frozen multi-core structure
real upstream core lift
NES compatibility
physical FPGA board support
RP2350 appliance readiness
Keystone86 PC integration
multi-ecosystem support
multi-board support
formal verification records under doc/VERIFICATION/
fully reconciled historical task files
```

These items belong to later rungs.

---

## 16. Current Next Position

According to the bringup ladder, after this refresh the project is positioned to begin:

```text
Rung 5: Existing Simulation Spine Verification Record
```

The next planned file is a formal verification record under:

```text
doc/VERIFICATION/
```

A likely filename is:

```text
doc/VERIFICATION/rung5_existing_simulation_spine.md
```

This source-of-truth map does not itself start that work.

A future active task/rung file or explicit human instruction must authorize that work.

---

## 17. Conflict Rule

If this source-of-truth map conflicts with:

```text
AGENTS.md
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/multi_core_structure.md
doc/core_lift_sim_contract.md
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/task_template.md
```

stop and resolve the conflict explicitly.

Do not silently reinterpret authority documents.

Do not use this map to override higher-authority design, roadmap, ladder, structure, core-lift, process, agent, or task-template documents.

---

## 18. One-Sentence Summary

The current Mistable repo truth is a working deterministic simulation spine plus an established design/roadmap/ladder/source-of-truth/agent-workflow/code-review/task-template/agent-rules authority system, with historical task files and formal verification records pending later reconciliation or creation.
