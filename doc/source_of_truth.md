# Mistable Source of Truth Map

Status: Draft v0.1  
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
doc/master_design_statement.md
    Root design identity.
    Defines what Mistable is and must remain.

doc/ROADMAP.md
    Big-picture development phases.
    Defines where Mistable goes over time.

doc/bringup_ladder.md
    Ordered proof rungs.
    Defines what order work happens in.

doc/multi_core_structure.md
    Frozen repository structure and long-term integration policy.
    Defines the intended framework/core/ecosystem/board/build-control structure.

doc/core_lift_sim_contract.md
    Frozen simulation-first core lift contract.
    Defines how upstream cores are to be lifted into the simulation-first path.
```

These files describe the current project direction and future structure.

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
standing execution-agent rules from the earlier Phase 0 workflow
```

Current reality:

```text
AGENTS.md exists
AGENTS.md still describes the older Phase 0 Minimal Spine context
AGENTS.md does not yet fully reference the new master design statement / roadmap / bringup ladder system
```

Current treatment:

```text
AGENTS.md remains important historical and active agent guidance
AGENTS.md should be updated in a later rung after the process docs and task template exist
AGENTS.md must not be silently ignored by coding agents
AGENTS.md must not override newer root authority documents if a conflict is discovered
```

Non-claim:

```text
AGENTS.md is not yet fully reconciled with the new document system
```

---

## 4. Current Historical Task Files

The current repository contains historical task files under:

```text
doc/TASKS/
```

Current known task files:

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

## 5. Current Implementation Baseline

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

## 6. Current Build and Control Files

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

## 7. Current Container and Environment Files

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

## 8. Current Test and Verification Files

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

## 9. Current Documentation Files

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

## 10. Current Frozen Architecture Documents

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

## 11. Current Missing Planned Documents

The current document system references files that are planned but not yet complete.

Known planned documents include:

```text
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/task_template.md
doc/VERIFICATION/<rung>.md
```

Current treatment:

```text
these files are expected by the document system
they should be created in future rungs
they should not be assumed to exist until they are committed
```

Non-claim:

```text
agent workflow procedure is not yet fully defined in the new document system
code review procedure is not yet fully defined in the new document system
task/rung template is not yet fully defined in the new document system
formal verification records do not yet exist under doc/VERIFICATION/
```

---

## 12. What Is Currently Proven

The current repo proves, at most:

```text
there is an existing minimal deterministic simulation spine
the simulation can produce an observable build artifact
the repo has a Docker-oriented development environment
the repo has Make/script entry points for current smoke verification
the repo has a golden hash file for the current frame artifact
the project now has a root design statement, roadmap, and bringup ladder
the project has frozen long-term structure and core-lift policy documents
```

This is the current baseline.

---

## 13. What Is Not Currently Proven

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
fully updated AGENTS.md authority alignment
```

These items belong to later rungs.

---

## 14. Current Next Position

According to the bringup ladder, after this file exists the project is positioned to proceed toward:

```text
Rung 3: Agent Workflow and Review Process
```

This source-of-truth map does not itself start Rung 3.

A future active task/rung file must authorize that work.

---

## 15. Conflict Rule

If this source-of-truth map conflicts with:

```text
doc/master_design_statement.md
doc/ROADMAP.md
doc/bringup_ladder.md
doc/multi_core_structure.md
doc/core_lift_sim_contract.md
```

stop and resolve the conflict explicitly.

Do not silently reinterpret authority documents.

Do not use this map to override higher-authority design, roadmap, ladder, structure, or core-lift documents.

---

## 16. One-Sentence Summary

The current Mistable repo truth is a working deterministic simulation spine plus a newly established design/roadmap/ladder authority system, with historical task files and older agent rules pending later reconciliation.
