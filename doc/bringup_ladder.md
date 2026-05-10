# Mistable Bringup Ladder

Status: Draft v0.1  
Role: Ordered proof rungs

---

## 1. Purpose

This document defines the ordered proof rungs for Mistable bring-up.

It is downstream from:

```text
doc/master_design_statement.md
doc/ROADMAP.md
```

The master design statement defines what Mistable is and must remain.

The roadmap defines where Mistable goes over time.

This bringup ladder defines what order work happens in.

This document does not authorize implementation by itself.

Active implementation authority belongs in task/rung files under:

```text
doc/TASKS/
```

Agent execution behavior belongs in:

```text
AGENTS.md
doc/process/
```

Repository structure and long-term integration policy are governed by:

```text
doc/multi_core_structure.md
```

Simulation-first core lift work is governed by:

```text
doc/core_lift_sim_contract.md
```

---

## 2. Ladder Role

The bringup ladder answers:

```text
What must be proven first?
What comes next?
What does each rung prove?
What does each rung explicitly not prove?
What must not be skipped?
```

The bringup ladder does not answer:

```text
What exact files may change in the active task?
What exact commands must be run for the active task?
What is the coding-agent session procedure?
What is the review format?
What is the verification record for a completed rung?
```

Those responsibilities belong to:

```text
doc/TASKS/<active_rung>.md
doc/process/agent_workflow.md
doc/process/code_review.md
doc/VERIFICATION/<rung>.md
```

---

## 3. Current Position After This File Is Committed

The current repository already contains an existing deterministic simulation spine.

That means Rung 0 is recognized as already present in the repo.

This file creates the bringup ladder itself.

That means Rung 1 becomes satisfied when this document is committed, assuming the master design statement and roadmap are already present.

After this file is committed, the next active work should begin at:

```text
Rung 2: Current Source-of-Truth Map
```

Do not restart from Rung 0 unless a later review invalidates the existing baseline.

Do not treat historical task files as active authority merely because they already exist.

Historical task reconciliation is handled later in this ladder.

---

## 4. Historical Task Files

Existing task files under:

```text
doc/TASKS/
```

may predate this bringup ladder.

Until reviewed and explicitly reconciled, historical task files do not define the current bringup sequence and must not be treated as active authority.

A historical task becomes active only when:

```text
it is reviewed against doc/master_design_statement.md
it is reviewed against doc/ROADMAP.md
it is reviewed against this bringup ladder
it is updated or replaced as needed
a human project owner explicitly names it as the active task/rung
```

Out-of-sequence historical tasks, including physical hardware or appliance work, should be deferred rather than deleted unless a later cleanup task explicitly decides otherwise.

Historical work may still be useful as reference material.

Historical work must not override the current document system.

---

## 5. Global Bringup Rules

### 5.1 Do Not Skip Rungs

A later rung must not begin until the prior required rung is either:

```text
verified
explicitly deferred
explicitly replaced by a corrective rung
```

Do not skip a rung merely because later work seems more interesting or useful.

### 5.2 Do Not Expand by Inference

A rung proves only what it says it proves.

A rung does not prove future-rung behavior by implication.

If a feature is not authorized by the active task/rung file, it is out of scope.

### 5.3 Verification Controls Claims

A rung is not complete merely because code exists.

A rung is complete only when the required verification exists and the resulting claims are recorded in the appropriate verification record or task completion record.

### 5.4 Stubs Are Not Features

A stub, interface name, placeholder file, or empty wrapper does not prove that a resource exists.

Resources become real only when the active rung defines their scope and verification records what passed.

### 5.5 Simulation First

Simulation remains the first-class bring-up path.

Physical hardware work may be researched or preserved historically, but it must not become the main dependency before the simulation and virtual-board path are proven.

### 5.6 Virtual Board Before Physical Board Dependency

The virtual board path must be proven before physical FPGA board or MCU-backed appliance work becomes a required dependency.

Physical board work belongs later in the ladder unless a human project owner explicitly creates a limited research task that does not disturb the main bringup path.

### 5.7 Smaller Whole-Machine Cores Before Keystone86 PC

Mistable should prove the platform path with a smaller whole-machine core before attempting Keystone86 PC integration.

A NES-compatible core is the preferred first real-core class, but exact core selection and execution details belong in active task/rung files and the core-lift contract.

### 5.8 Existing Frozen Structure Must Be Respected

Future structure and core-lift work must respect:

```text
doc/multi_core_structure.md
doc/core_lift_sim_contract.md
```

If this bringup ladder appears to conflict with either of those documents, stop and resolve the conflict explicitly.

---

## 6. Rung Overview

The current intended ladder is:

```text
Rung 0  Existing deterministic simulation spine baseline
Rung 1  Document system baseline
Rung 2  Current source-of-truth map
Rung 3  Agent workflow and review process
Rung 4  Task/rung template
Rung 5  Existing simulation spine verification record
Rung 6  Repository structure migration planning
Rung 7  Simulation tuple skeleton
Rung 8  Migrated simulation spine preserved
Rung 9  Monitor console skeleton
Rung 10 Monitor smoke verification
Rung 11 Virtual board foundation
Rung 12 Bounded event/status model
Rung 13 Demo core through virtual board
Rung 14 First real core lift classification
Rung 15 First real core wrapper skeleton
Rung 16 First real core observable smoke
Rung 17 Virtual board resource growth
Rung 18 Virtual-to-physical mapping preparation
Rung 19 Larger whole-machine core preparation
Rung 20 Ecosystem and board expansion
```

This overview defines intended order only.

Exact implementation tasks must be created separately under:

```text
doc/TASKS/
```

---

## 7. Rung 0: Existing Deterministic Simulation Spine Baseline

### Purpose

Recognize the existing minimal simulation spine as the starting point.

The current repo already has a small deterministic simulation path that predates this ladder.

### Proves

```text
the repo has an existing simulation entry point
the repo can produce observable simulation output or artifact
there is already a minimal RTL/testbench spine to preserve
```

### Does Not Prove

```text
full virtual board behavior
monitor behavior
service-link behavior
multi-core structure compliance
real core support
physical board readiness
```

### May Start After

```text
doc/master_design_statement.md exists
doc/ROADMAP.md exists
```

### Next Likely Rung

```text
Rung 1: Document system baseline
```

---

## 8. Rung 1: Document System Baseline

### Purpose

Establish the core document system required for controlled AI-assisted development.

### Proves

```text
root design identity exists
roadmap exists
bringup ladder exists
document roles are explicit
historical task files are not current authority until reconciled
```

### Does Not Prove

```text
agent workflow is complete
task template is complete
code review process is complete
source-of-truth map is complete
any implementation behavior
```

### May Start After

```text
Rung 0 is recognized
```

### Next Likely Rung

```text
Rung 2: Current source-of-truth map
```

---

## 9. Rung 2: Current Source-of-Truth Map

### Purpose

Create a lightweight map of current repo truth so agents do not guess which files own which facts.

### Proves

```text
current important repo files are identified
current build/test entry points are identified
current architecture authority files are identified
current historical task files are identified as pending reconciliation
current generated or expected artifacts are identified
```

### Does Not Prove

```text
repo structure migration
virtual board behavior
monitor behavior
core lift readiness
historical task alignment
```

### May Start After

```text
Rung 1 is complete
```

### Next Likely Rung

```text
Rung 3: Agent workflow and review process
```

---

## 10. Rung 3: Agent Workflow and Review Process

### Purpose

Define how ChatGPT, Claude Code, Codex, or similar agents operate inside the repo.

### Proves

```text
agent session procedure exists
handoff expectations exist
structured report expectations exist
review-only behavior is defined
tool/capability boundaries are defined
one-active-implementation-agent policy is defined
```

### Does Not Prove

```text
any implementation behavior
any virtual board feature
any monitor feature
any core-lift behavior
```

### May Start After

```text
Rung 2 is complete
```

### Next Likely Rung

```text
Rung 4: Task/rung template
```

---

## 11. Rung 4: Task/Rung Template

### Purpose

Create the standard developer-directive shape for future active work.

### Proves

```text
future task/rung files have a consistent required structure
authorized scope can be stated explicitly
blocked scope can be stated explicitly
acceptance expectations can be stated explicitly
non-claims can be stated explicitly
stop conditions can be stated explicitly
```

### Does Not Prove

```text
any task has been executed
any implementation behavior
any existing historical task is aligned
```

### May Start After

```text
Rung 3 is complete
```

### Next Likely Rung

```text
Rung 5: Existing simulation spine verification record
```

---

## 12. Rung 5: Existing Simulation Spine Verification Record

### Purpose

Formally record what the existing simulation spine proves under the new document system.

### Proves

```text
the existing simulation spine can be verified under current process rules
commands used for verification are recorded
observable output or artifact is recorded
current claims are bounded
current non-claims are explicit
```

### Does Not Prove

```text
full virtual board behavior
monitor behavior
service-link behavior
repo structure migration
real core support
physical board readiness
```

### May Start After

```text
Rung 4 is complete
```

### Next Likely Rung

```text
Rung 6: Repository structure migration planning
```

---

## 13. Rung 6: Repository Structure Migration Planning

### Purpose

Plan how the current minimal/pre-structural repo will move toward the frozen multi-core structure.

### Proves

```text
the current flat/minimal layout has been compared to doc/multi_core_structure.md
required structural migration steps are identified
migration risks are identified
behavior-preservation requirements are identified
first tuple target is proposed
historical task conflicts are identified but not necessarily resolved
```

### Does Not Prove

```text
files have moved
tuple build works
virtual board exists
core lift readiness
NES integration
```

### May Start After

```text
Rung 5 is complete
```

### Next Likely Rung

```text
Rung 7: Simulation tuple skeleton
```

---

## 14. Rung 7: Simulation Tuple Skeleton

### Purpose

Introduce the first explicit tuple skeleton for simulation-oriented work.

The first target should align with:

```text
ECOSYSTEM=sim
BOARD=sim
```

### Proves

```text
the repo begins expressing CORE/ECOSYSTEM/BOARD selection
ECOSYSTEM=sim is visible
BOARD=sim is visible
the first simulation tuple can be named
build/control path can recognize the tuple shape
```

### Does Not Prove

```text
full multi-core framework
full virtual board behavior
NES support
physical board support
complete migration to final structure
```

### May Start After

```text
Rung 6 is complete
```

### Next Likely Rung

```text
Rung 8: Migrated simulation spine preserved
```

---

## 15. Rung 8: Migrated Simulation Spine Preserved

### Purpose

Move or wrap the existing simulation spine into the emerging structure while preserving its behavior.

### Proves

```text
existing deterministic simulation behavior survives structural migration
observable artifact or output remains available
Make/Docker path remains visible
the first simulation tuple can exercise the preserved spine
```

### Does Not Prove

```text
full virtual board behavior
monitor behavior
real core support
NES support
physical board readiness
```

### May Start After

```text
Rung 7 is complete
```

### Next Likely Rung

```text
Rung 9: Monitor console skeleton
```

---

## 16. Rung 9: Monitor Console Skeleton

### Purpose

Add the first human-facing monitor/status path.

### Proves

```text
a monitor can be launched through documented visible tooling
monitor can print human-readable status
monitor can expose help or command discovery
monitor can report attached/stubbed/unavailable board or core state honestly
monitor has color/no-color policy
monitor has non-interactive smoke path
```

### Does Not Prove

```text
FPGA interaction
MCU equivalence
service-link behavior
debugger capability
virtual board resource implementation
```

### May Start After

```text
Rung 8 is complete
```

### Next Likely Rung

```text
Rung 10: Monitor smoke verification
```

---

## 17. Rung 10: Monitor Smoke Verification

### Purpose

Verify the minimum working monitor behavior and record the claims.

### Proves

```text
monitor launch path works
monitor status output is visible
monitor help or command discovery works
monitor smoke path is automatable
monitor non-claims are explicit
```

### Does Not Prove

```text
real FPGA interaction
real MCU interaction
real service-link transport
real debugger behavior
virtual board resources
```

### May Start After

```text
Rung 9 is complete
```

### Next Likely Rung

```text
Rung 11: Virtual board foundation
```

---

## 18. Rung 11: Virtual Board Foundation

### Purpose

Begin turning the simulation spine into an explicit virtual board foundation.

### Proves

```text
virtual board identity exists in the repo
virtual board is connected to ECOSYSTEM=sim and BOARD=sim
board/core attachment concept exists at a bounded level
reset/status relationship is defined at a bounded level
unimplemented resources are clearly marked as non-claims
```

### Does Not Prove

```text
full RAM model
full storage model
full video/audio/input stack
real service-link transport
physical board readiness
NES support
```

### May Start After

```text
Rung 10 is complete
```

### Next Likely Rung

```text
Rung 12: Bounded event/status model
```

---

## 19. Rung 12: Bounded Event/Status Model

### Purpose

Define the first bounded status/event vocabulary between monitor, host service behavior, and virtual board concepts.

### Proves

```text
event/status categories are explicit
bounded event direction is defined
unbounded logging is not treated as FPGA communication
monitor can report event/status state honestly
future service-link behavior has a constrained vocabulary seed
```

### Does Not Prove

```text
real-time transport
hardware service-link behavior
MCU implementation
full debugger support
full input/audio/storage behavior
```

### May Start After

```text
Rung 11 is complete
```

### Next Likely Rung

```text
Rung 13: Demo core through virtual board
```

---

## 20. Rung 13: Demo Core Through Virtual Board

### Purpose

Prove that a simple concrete demo target can use the virtual board path.

### Proves

```text
a core-like unit can attach to the virtual board path
visible output or artifact exists
monitor/status can reflect bounded state
board/core boundary remains visible
non-claims remain explicit
```

### Does Not Prove

```text
upstream core portability
NES compatibility
Keystone86 readiness
physical board readiness
full virtual board resource set
```

### May Start After

```text
Rung 12 is complete
```

### Next Likely Rung

```text
Rung 14: First real core lift classification
```

---

## 21. Rung 14: First Real Core Lift Classification

### Purpose

Classify a smaller real whole-machine core candidate before implementation.

A NES-compatible core is the preferred first class unless later roadmap or ladder updates change that direction.

This rung must follow:

```text
doc/core_lift_sim_contract.md
```

### Proves

```text
upstream provenance is understood
candidate top-level modules are identified
clock/reset expectations are identified
video/audio/input/media expectations are identified
vendor primitive risks are identified
generated asset risks are identified
submodule or missing asset risks are identified
wrapper/adaptation boundary is identified
virtual board fit is assessed
stop conditions are documented
```

### Does Not Prove

```text
NES is playable
NES wrapper exists
upstream source has been modified
virtual board resources are complete
Keystone86 readiness
```

### May Start After

```text
Rung 13 is complete
```

### Next Likely Rung

```text
Rung 15: First real core wrapper skeleton
```

---

## 22. Rung 15: First Real Core Wrapper Skeleton

### Purpose

Create the first structural wrapper/adaptation skeleton for the selected smaller real core.

This rung must follow:

```text
doc/core_lift_sim_contract.md
doc/multi_core_structure.md
```

### Proves

```text
upstream source is kept intact where practical
local wrapper/adaptation boundary exists
source manifests or inclusion rules begin to exist
simulation tuple remains explicit
missing pieces remain explicit
```

### Does Not Prove

```text
playable core behavior
full compatibility
full virtual board resources
physical board readiness
Keystone86 readiness
```

### May Start After

```text
Rung 14 is complete
```

### Next Likely Rung

```text
Rung 16: First real core observable smoke
```

---

## 23. Rung 16: First Real Core Observable Smoke

### Purpose

Prove early observable behavior from the first real core through the virtual board path.

### Proves

```text
real core wrapper can be built or elaborated in the simulation path
reset or basic activity is observable
virtual board path participates in bounded form
monitor/status can report limited state
non-claims remain explicit
```

### Does Not Prove

```text
full compatibility
full gameplay
full audio/video/input correctness
physical board readiness
Keystone86 readiness
```

### May Start After

```text
Rung 15 is complete
```

### Next Likely Rung

```text
Rung 17: Virtual board resource growth
```

---

## 24. Rung 17: Virtual Board Resource Growth

### Purpose

Grow virtual board resources incrementally after a concrete demo and first real core smoke path exist.

### Proves

```text
individual resources can be added one at a time
each resource has explicit scope
each resource has explicit non-claims
resource work does not force unrelated framework expansion
```

### Does Not Prove

```text
all resources are complete
physical board readiness
Keystone86 readiness
multi-ecosystem support
```

### May Start After

```text
Rung 16 is complete
```

### Next Likely Rung

```text
Rung 18: Virtual-to-physical mapping preparation
```

---

## 25. Rung 18: Virtual-to-Physical Mapping Preparation

### Purpose

Prepare mappings from proven virtual board concepts toward physical FPGA boards and MCU-backed appliance paths.

### Proves

```text
virtual board concepts can be mapped toward real hardware
physical resource mapping questions are identified
MCU/service-plane mapping questions are identified
virtual board remains first-class
board/core boundary remains intact
```

### Does Not Prove

```text
physical board support is complete
RP2350 appliance is active
real hardware is required for development
Keystone86 readiness
```

### May Start After

```text
Rung 17 is complete
```

### Next Likely Rung

```text
Rung 19: Larger whole-machine core preparation
```

---

## 26. Rung 19: Larger Whole-Machine Core Preparation

### Purpose

Prepare for larger whole-machine cores after the smaller-core and virtual-board path is proven.

This includes future Keystone86 PC integration planning.

### Proves

```text
whole-machine core packaging expectations are understood
platform/core boundary can support larger systems in principle
PC-specific behavior remains inside the PC core
Mistable remains generic
risk from smaller-core experience is incorporated
```

### Does Not Prove

```text
Keystone86 PC is integrated
PC compatibility exists
full chipset behavior exists in Mistable
physical board support is complete
```

### May Start After

```text
Rung 18 is complete
```

### Next Likely Rung

```text
Rung 20: Ecosystem and board expansion
```

---

## 27. Rung 20: Ecosystem and Board Expansion

### Purpose

Expand toward multiple ecosystems and boards after the virtual board, smaller core lift, and physical mapping concepts are proven.

### Proves

```text
multi-ecosystem direction can begin safely
multi-board direction can begin safely
compatibility matrix can be made explicit
source manifests and wrappers remain controlled
upstream core boundaries remain protected
```

### Does Not Prove

```text
every ecosystem is supported
every board is supported
every core is portable
framework expansion is unlimited
```

### May Start After

```text
Rung 19 is complete
```

### Next Likely Rung

```text
future roadmap update
```

---

## 28. Reconciliation of Historical Tasks

Existing historical task files should be reconciled after the core document system exists.

Reconciliation should classify each historical task as one of:

```text
already completed and recordable
still valid but needs formatting/update
valid concept but out of sequence
superseded by newer roadmap/ladder direction
deferred future work
archival reference only
```

Historical task reconciliation must not change the bringup order unless the roadmap and ladder are explicitly updated.

---

## 29. Relationship to Active Work

This bringup ladder does not select the active task.

A task becomes active only when a human project owner or active prompt names the task/rung file under:

```text
doc/TASKS/
```

This bringup ladder does not authorize coding agents to implement future rungs.

Coding agents must follow:

```text
AGENTS.md
doc/process/agent_workflow.md
doc/TASKS/<active_rung>.md
```

If this bringup ladder appears to conflict with the master design statement or roadmap, stop and resolve the conflict explicitly.

Do not silently reinterpret any authority document.

---

## 30. One-Sentence Summary

Mistable climbs from the existing deterministic simulation spine toward a structured simulation tuple, monitor-first accessibility, a proven virtual board, a smaller real core lift, and only later physical mappings and larger whole-machine cores such as Keystone86 PC.
