# mistable

`mistable` is a simulation-first, MiSTer-inspired FPGA platform project.

The current repository has two important layers:

```text
1. A working Phase 0 deterministic simulation spine
2. A document-control stack for disciplined AI-assisted development
```

The simulation spine proves that the repo can build and run a small deterministic Verilator simulation and produce a real output artifact.

The document-control stack defines how future work is planned, reviewed, verified, and kept inside scope.

---

## Current Status

Current baseline:

```text
Document-control stack:
    present

Existing deterministic simulation spine:
    present

Formal simulation-spine verification record:
    not started

Virtual board:
    not implemented

Monitor/debugger:
    not implemented

CORE/ECOSYSTEM/BOARD tuple migration:
    not implemented

Real upstream core lift:
    not started

Physical board / RP2350 appliance work:
    deferred until later roadmap position
```

The project is currently positioned immediately before:

```text
Rung 5: Existing Simulation Spine Verification Record
```

Rung 5 has not started.

---

## Root Project Intent

Mistable exists to let FPGA-style systems be developed, simulated, inspected, and eventually mapped to real hardware without requiring physical FPGA bring-up as the first step.

Whole-machine cores are intended to move through the path:

```text
simulation
    → virtual board
        → real FPGA board
```

Whole-machine cores are not the final stage of the path. They are the systems carried through the path.

A Mistable core may be a small logic block, but it may also be a complete machine such as:

```text
NES-compatible system
PC-compatible system
arcade board
console
computer
custom FPGA appliance
```

The root design identity is defined by:

```text
doc/master_design_statement.md
```

---

## Document-Control Stack

Mistable now uses a document-control stack so humans and AI coding agents do not have to infer project direction from chat history or unstated intent.

The current document-control stack is:

```text
CLAUDE.md
    Claude Code entry point.
    Directs Claude Code to read AGENTS.md for all standing rules and authority.

AGENTS.md
    Standing rules for coding and review agents.

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
    Defines session modes, authority reading order, reporting, handoff,
    tool/capability boundaries, and stop conditions.

doc/process/code_review.md
    Review procedure.
    Defines read-only review, dirty-diff review, scope checks,
    protected-file checks, acceptance-evidence checks, and review output.

doc/TASKS/task_template.md
    Standard developer-directive shape.
    Defines how future task/rung packets should be written.

doc/VERIFICATION/document_control_stack_baseline.md
    Documentation-only baseline record.
    Records that the document-control stack exists and is role-consistent.

doc/multi_core_structure.md
    Frozen repository structure and long-term integration policy.

doc/core_lift_sim_contract.md
    Frozen simulation-first upstream core lift contract.
```

The document-control stack is intentionally separated by role:

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

Verification records:
    what actually passed and what is actually proven
```

No document should silently replace another document’s role.

---

## AI-Agent Workflow

Coding agents are contributors, not architects.

Agents must not infer project direction from:

```text
chat history
prior sessions
tool availability
unstated intent
apparent next steps
```

Agents must use written repo authority.

The normal authority entry point is:

```text
AGENTS.md
```

Implementation work requires an explicitly named active task/rung file under:

```text
doc/TASKS/
```

The roadmap and bringup ladder define direction and order, but they do not authorize implementation by themselves.

Tool availability is not permission.

Review is read-only unless explicitly authorized otherwise.

---

## Historical Task Files

The repository contains historical task files under:

```text
doc/TASKS/
```

Known historical task files include:

```text
doc/TASKS/000_phase0_minimal_spine.md
doc/TASKS/001_container_first_runner.md
doc/TASKS/002_phase1_rp2350_pizero_appliance.md
```

These files may describe completed work, useful historical intent, or out-of-sequence future work.

They are pending reconciliation.

They are not automatically current active authority.

A historical task becomes active only when:

```text
it is reviewed against doc/master_design_statement.md
it is reviewed against doc/ROADMAP.md
it is reviewed against doc/bringup_ladder.md
it is updated or replaced as needed
a human project owner explicitly names it as the active task/rung
```

The RP2350 appliance task is currently considered out of sequence under the new roadmap until the virtual-board path is proven.

---

## Current Implementation Baseline

The current implementation baseline is the existing deterministic simulation spine.

Current implementation files:

```text
rtl/mistable_top.sv
sim/tb.cpp
sim/frame.ppm.sha256
```

Current generated artifact:

```text
build/frame.ppm
```

The artifact is a binary **PPM P6** image generated by the simulation.

The current simulation spine is useful and should be preserved, but it does not yet prove:

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
```

---

## Current Working Baseline Commands

Canonical entry points:

```text
./dev
./scripts/sanity.sh
./scripts/test.sh
```

Canonical container/tool definition:

```text
container/Dockerfile
```

Canonical container runner:

```text
scripts/docker.sh
```

Shell defaults for interactive container sessions:

```text
scripts/bashrc
```

Golden smoke verification file:

```text
sim/frame.ppm.sha256
```

---

## Quick Start

### Enter the trusted container shell

```sh
./dev
```

### Verify the environment

Run this inside the container:

```sh
./scripts/sanity.sh
```

This checks the current environment and baseline repo expectations.

### Run the current smoke test

```sh
./scripts/test.sh
```

This is the current smoke verification path for the existing simulation spine.

---

## Verification Workflow

The current smoke verification path is:

```sh
./scripts/test.sh
```

This script:

```text
cleans previous build output
builds the simulation
runs the simulation
checks that build/frame.ppm exists
computes the artifact SHA-256
compares it against sim/frame.ppm.sha256
prints PASS when the artifact matches the golden hash
```

This script is useful current verification machinery, but it has not yet been recorded as a formal rung verification record under:

```text
doc/VERIFICATION/
```

That is future Rung 5 work.

---

## Makefile Shortcuts

The repository exposes common workflow steps through `make`:

```sh
make sim
make clean
make shell
make sanity
make golden
```

Target summary:

```text
make sim
    Build and run the current Verilator simulation.

make clean
    Remove generated build output.

make shell
    Enter the trusted container shell through ./dev.

make sanity
    Run ./scripts/sanity.sh.

make golden
    Intentionally refresh the golden smoke hash.
```

The current Makefile does not yet express the future `CORE/ECOSYSTEM/BOARD` tuple model.

That belongs to later structure-migration rungs.

---

## Initializing or Updating the Golden Hash

The golden hash is stored at:

```text
sim/frame.ppm.sha256
```

To intentionally refresh it:

```sh
UPDATE_GOLDEN=1 ./scripts/test.sh
```

Or:

```sh
make golden
```

Only do this when the output change is intentional and verified.

Do not update the golden hash casually.

---

## Running on Host

You can invoke the test script directly from the repo root:

```sh
./scripts/test.sh
```

Or use:

```sh
make sim
```

The preferred development path remains the trusted container workflow.

---

## Running via Docker Manually

To build and run the container directly:

```sh
docker build -t mistable-dev -f container/Dockerfile .
docker run --rm -it -v "$PWD:/work" -w /work mistable-dev ./scripts/test.sh
```

---

## Interactive Container Behavior

The `./dev` entrypoint launches an interactive shell inside the canonical container environment.

That shell is configured through:

```text
scripts/docker.sh
scripts/bashrc
```

Current interactive shell defaults include:

```text
colored ls
ll alias
la alias
```

---

## Long-Term Structure Direction

The long-term repository structure and integration policy are governed by:

```text
doc/multi_core_structure.md
```

That policy establishes a disciplined, portable structure intended to support multiple ecosystems and boards.

The long-term structural layers are:

```text
framework
core
ecosystem
board
build/control
```

In practical terms:

```text
framework/
    reusable internal contracts

cores/
    per-core integration logic

ecosystems/
    environment-specific behavior

boards/
    physical or virtual board realization

external/
    imported third-party upstream cores

Makefiles and scripts
    explicit build/control selection and validation
```

The current repo has not yet been migrated into that full structure.

That migration belongs to later bringup rungs.

---

## Core-Lift Direction

Simulation-first upstream core lifting is governed by:

```text
doc/core_lift_sim_contract.md
```

Real upstream core lifts should not proceed until the required document and structure rungs are reached.

A smaller whole-machine core class, such as a NES-compatible core, is the preferred first real-core direction before larger whole-machine work such as Keystone86 PC integration.

Keystone86 integration is intentionally deferred until the platform path is proven with smaller concrete targets.

---

## Current Non-Claims

The current repo does not yet claim:

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
formal simulation-spine verification record
historical task reconciliation
```

Stubs, placeholders, wrappers, interface names, TODOs, or planned files are not features.

A resource exists only when the active rung defines its scope and verification records what passed.

---

## Next Safe Position

The document-control stack is now present.

The next implementation-baseline step, if explicitly authorized later, is:

```text
Rung 5: Existing Simulation Spine Verification Record
```

That would create a formal verification record under:

```text
doc/VERIFICATION/
```

Rung 5 has not started in this README refresh.

This README refresh does not verify the simulation spine.

---

## Repository Baseline Contract

The current development baseline is:

```text
container/Dockerfile
    defines the tool room

./dev
    standard interactive container entry

./scripts/sanity.sh
    standard environment gate

./scripts/test.sh
    standard smoke/build verification path

sim/frame.ppm.sha256
    current golden smoke hash

build/frame.ppm
    current generated simulation artifact
```

The current document-control baseline is:

```text
CLAUDE.md
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

---

## Summary

Mistable currently has a working deterministic simulation spine and a reconciled document-control system.

The project is now positioned to govern future work through written authority, active task/rung packets, review procedure, and explicit verification records rather than chat history or agent inference.
