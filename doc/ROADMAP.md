# Mistable Roadmap

Status: Draft v0.2  
Role: Big-picture development phases

---

## 1. Purpose

This roadmap defines where Mistable goes over time.

It is downstream from:

```text
doc/master_design_statement.md
```

The master design statement defines what Mistable is and must remain.

This roadmap translates that root design identity into major development phases.

This roadmap does not authorize current implementation by itself.

Exact implementation scope belongs in active task/rung files under:

```text
doc/TASKS/
```

Exact ordering and proof requirements belong in:

```text
doc/bringup_ladder.md
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

## 2. Roadmap Role

The roadmap answers:

```text
Where is Mistable going?
What major phases must exist?
How do virtual board, real hardware, core lifts, and whole-machine cores relate?
How does the current repo move toward the frozen structure?
```

The roadmap does not answer:

```text
What files may change right now?
What command proves the current rung?
What is the active implementation scope?
What is the exact agent workflow?
What is the current verification record?
```

Those responsibilities belong to the document system defined in the master design statement.

---

## 3. Governing Architecture Inputs

The roadmap must remain consistent with these already-existing architecture documents.

### 3.1 Multi-Core Structure Policy

The long-term repository structure is governed by:

```text
doc/multi_core_structure.md
```

That document defines the structural model for:

```text
framework
cores
ecosystems
boards
external upstream cores
build/control
```

It also defines the intended separation between:

```text
core logic
ecosystem conventions
physical or virtual board realization
build/control selection
```

The current repository may not yet be fully migrated into that structure.

That mismatch must be resolved through explicit bring-up rungs before real core-lift work is treated as structurally complete.

### 3.2 Simulation-First Core Lift Contract

Simulation-first upstream core lifts are governed by:

```text
doc/core_lift_sim_contract.md
```

That document defines the required approach for lifting upstream cores into the simulation-first path.

The roadmap may identify core-lift phases, but the core-lift contract controls how those lifts are performed.

### 3.3 Tuple Model

Mistable’s long-term selection model is based on explicit tuples:

```text
CORE=<core>
ECOSYSTEM=<ecosystem>
BOARD=<board>
```

The first structural target for simulation-oriented work should be:

```text
ECOSYSTEM=sim
BOARD=sim
```

The virtual board concept must map cleanly onto the simulation ecosystem and simulation board model.

The virtual board is not a separate architecture outside the tuple model.

---

## 4. Roadmap Invariants

The following sequencing rules apply across the roadmap.

### 4.1 Simulation Before Hardware Dependency

Mistable must prove meaningful behavior in simulation before depending on physical FPGA hardware.

Physical board work may be planned, researched, or prepared, but the virtual/simulation path must remain the first-class bring-up path.

### 4.2 Virtual Board Before Real Board Dependency

The virtual board must become the first practical board target.

In structural terms, the first virtual board path should align with:

```text
ECOSYSTEM=sim
BOARD=sim
```

Real FPGA boards and MCU-backed appliances should map to the same platform concepts later.

They must not replace the virtual board as the first accessibility and development target.

### 4.3 Smaller Whole-Machine Cores Before Keystone86 PC

Before attempting a Keystone86-based PC-compatible whole-machine core inside Mistable, Mistable should prove the platform path with smaller and more approachable whole-machine cores.

A NES-compatible core is the preferred first real-core class because it can exercise video, audio, input, reset, ROM/media loading, and simulation observability without PC-class chipset complexity.

The exact first real-core sequence belongs in:

```text
doc/bringup_ladder.md
```

NES structural work must also respect the first-milestone guidance already defined in:

```text
doc/multi_core_structure.md
```

### 4.4 Concrete Proof Before Framework Expansion

Mistable must avoid building broad abstractions before repeated concrete behavior justifies them.

Abstraction must follow working cases.

It must not precede them.

### 4.5 Whole-Machine Cores Travel Through the Path

Whole-machine cores are not the final stage of the roadmap.

They are the systems carried through the development path:

```text
simulation
    → virtual board
        → real FPGA board
```

The same core concept should remain understandable across those stages.

---

## 5. Phase Overview

The roadmap is organized into broad phases.

These phases describe direction only.

They are not active task authorization.

---

## Phase A: Baseline Identity and Document System

Mistable first establishes the written development-control system.

This phase defines:

```text
root design identity
document authority roles
roadmap direction
bring-up ladder structure
task/rung template structure
agent workflow expectations
review expectations
source-of-truth mapping
verification record expectations
```

The purpose of this phase is to make the project safe for AI-assisted development before the codebase becomes large.

This phase exists so coding agents act like bounded developer team members rather than autonomous architects.

Expected outcomes:

```text
master design statement exists
roadmap exists
bringup ladder exists
task/rung template exists
agent workflow document exists
code review document exists
source-of-truth map exists
verification record location exists
```

Non-goals:

```text
no new broad framework
no virtual board implementation requirement
no real core lift requirement
no hardware dependency
```

---

## Phase B: Existing Simulation Spine Preservation

Mistable preserves and clarifies the existing deterministic simulation spine.

This phase keeps the current minimal simulation path meaningful while the document system is established around it.

The existing spine represents the first proof that Mistable can produce observable behavior without physical FPGA hardware.

Expected direction:

```text
preserve deterministic simulation behavior
preserve generated observable artifact behavior
preserve Docker/Make development path
preserve explicit command-driven workflow
document what the current spine proves
document what the current spine does not prove
```

Non-goals:

```text
no claim of full virtual board
no claim of monitor/service-link behavior
no claim of real core support
no claim of physical board readiness
no claim that the repo already matches the frozen multi-core structure
```

---

## Phase C: Repository Structure Migration Toward Frozen Policy

Mistable must migrate from the current minimal/pre-structural spine toward the frozen architecture defined by:

```text
doc/multi_core_structure.md
```

This phase exists because real core-lift work depends on the structural separation between framework, cores, ecosystems, boards, external upstream sources, and build/control.

This phase should preserve existing working simulation behavior while moving the repository toward the structure required for future core lifts.

Expected direction:

```text
introduce the structural concepts required by doc/multi_core_structure.md
establish the first simulation tuple shape
align the existing simulation spine with CORE/ECOSYSTEM/BOARD selection
preserve the existing observable simulation proof during migration
make ECOSYSTEM=sim and BOARD=sim explicit
avoid changing behavior merely for layout movement
```

The first structural target should support the idea of:

```text
CORE=<demo-or-current-spine>
ECOSYSTEM=sim
BOARD=sim
```

The exact tuple names and file movements belong in the bring-up ladder and active task/rung files.

Non-goals:

```text
no real upstream core lift yet
no broad framework expansion beyond what migration requires
no physical-board dependency
no NES integration claim
no Keystone86 integration claim
no behavior claim lost during file movement
```

---

## Phase D: Monitor-First Accessibility Layer

Mistable adds a human-facing monitor/status path as part of the accessibility goal.

The monitor should make the system feel inspectable and approachable before the virtual board is complete.

This phase should establish the user-facing shape of interaction without claiming unsupported FPGA, MCU, service-link, or debugger behavior.

Expected direction:

```text
terminal-visible monitor/status path
human-readable system state
clear stubbed/unavailable state reporting
color/no-color policy
non-interactive smoke path
bounded status/event vocabulary at the user-interface level
```

Non-goals:

```text
no full debugger
no symbolic debugger
no unbounded FPGA printf/log stream
no claim of real FPGA interaction until proven
no claim of MCU equivalence until proven
```

---

## Phase E: Virtual Board Foundation

Mistable grows the simulation spine into a virtual board foundation.

This phase begins turning isolated simulation behavior into a board-like environment with explicit boundaries.

The virtual board should remain concrete and visible.

It must not become a broad abstraction framework before working behavior exists.

The virtual board must align with the simulation tuple model:

```text
ECOSYSTEM=sim
BOARD=sim
```

Expected direction:

```text
clear virtual board identity
bounded reset/status/event model
initial board/core attachment concept
initial resource ownership boundaries
visible non-claims for unimplemented resources
explicit relationship to ECOSYSTEM=sim and BOARD=sim
```

The virtual board is not considered working merely because interface names or placeholder files exist.

It becomes real only through visible behavior and recorded verification.

Non-goals:

```text
no full RAM subsystem unless authorized by a later rung
no full storage subsystem unless authorized by a later rung
no full video/audio/input stack unless authorized by later rungs
no generic plugin framework
no physical-board dependency
```

---

## Phase F: Virtual Board Resource Growth

Mistable incrementally grows virtual board resources after the foundation exists.

Resource work should proceed through small ordered proofs.

Potential resource families include:

```text
working memory / fast RAM model
large storage / media image model
video output path
audio output path
keyboard / mouse / joystick input model
service/debug/event transport
ROM or asset loading path
```

Each resource becomes real only when the bring-up ladder and active task define its scope and verification records what passed.

Non-goals:

```text
no resource exists merely because it has a stub
no resource exists merely because it has an interface name
no resource should force unrelated resources to be implemented early
```

---

## Phase G: Demo Core Through Virtual Board

Mistable should prove the virtual board path with a small concrete demo target before attempting a real upstream core lift.

This phase demonstrates that a core-like unit can use the board path in a visible, inspectable way.

Expected direction:

```text
simple concrete demo target
visible output or artifact
monitor/status visibility
bounded reset/status behavior
clear board/core boundary
explicit non-claims
```

Non-goals:

```text
no claim of upstream-core portability
no claim of NES compatibility
no claim of Keystone86 readiness
no claim of physical-board readiness
```

---

## Phase H: First Real Core Lift Classification

Mistable should next prove that the virtual board path can host a smaller whole-machine core class.

A NES-compatible core is the preferred first real-core class because it is complex enough to exercise the platform but much smaller than a PC-compatible system.

This phase begins with classification, not implementation.

Core-lift classification must follow the governing contract:

```text
doc/core_lift_sim_contract.md
```

NES structural expectations should also respect the first-milestone definition already captured in:

```text
doc/multi_core_structure.md
```

Expected direction:

```text
upstream core provenance understood
core top-level interfaces identified
clock/reset behavior identified
video/audio/input/media expectations identified
vendor primitive and generated asset risks identified
wrapper/adaptation boundary identified
virtual board fit assessed
missing upstream assets or submodules identified
stop conditions documented
```

Non-goals:

```text
no immediate claim of playable NES
no casual upstream rewrite
no board-specific assumptions hidden inside upstream source
no Keystone86 PC integration
no bypass of doc/core_lift_sim_contract.md
```

---

## Phase I: First Real Core Wrapper and Observable Smoke

After classification, Mistable should wrap and exercise the first real core through the virtual board path.

This phase proves structural integration and early observable behavior.

Implementation must follow:

```text
doc/core_lift_sim_contract.md
```

Expected direction:

```text
upstream source kept intact where practical
local wrapper/adaptation files own integration
virtual board supplies generic resources
simulation tuple remains explicit
observable reset or activity exists
monitor/status can report bounded state
non-claims remain explicit
```

Non-goals:

```text
no full compatibility claim without later proof
no broad multi-core framework expansion
no physical-board dependency
no violation of upstream/source boundary rules
```

---

## Phase J: Virtual-to-Physical Mapping Preparation

After the virtual board proves useful with concrete targets, Mistable may prepare mappings toward physical FPGA boards and MCU-backed appliance paths.

This phase should translate already-proven platform concepts toward real hardware without making real hardware the primary development dependency.

Expected direction:

```text
identify physical board resource mappings
identify MCU/service-plane mapping
preserve virtual board as first-class target
preserve board/core boundary
avoid single-board lock-in
```

Potential physical/service paths may include:

```text
FPGA board targets
RP2350 or similar service appliance concepts
USB CDC or serial monitor mapping
real input/storage/video/audio mappings
```

Non-goals:

```text
no physical board becomes the only supported path
no RP2350-specific architecture takeover
no board-specific behavior leaks into generic core boundaries
```

---

## Phase K: Larger Whole-Machine Core Preparation

Only after smaller whole-machine cores and the virtual board path are proven should Mistable prepare for larger whole-machine cores.

This includes future PC-compatible whole-machine work.

Keystone86 is expected to remain a separate CPU / PC-compatible machine effort until Mistable has proven the platform path well enough to host it cleanly.

Expected direction:

```text
define whole-machine core packaging expectations
preserve generic platform resources
keep PC-specific chipset behavior inside the PC core
avoid making Mistable itself PC-specific
use prior smaller-core experience to reduce risk
```

Non-goals:

```text
no early Keystone86 PC drop-in before platform readiness
no PC-specific platform takeover
no shortcut around virtual board proof
```

---

## Phase L: Ecosystem and Board Expansion

After the virtual board, smaller core lift, and physical mapping concepts are proven, Mistable may expand toward multiple ecosystems and boards.

This phase should follow the existing structural policy:

```text
doc/multi_core_structure.md
```

Expected direction:

```text
multiple ecosystem targets
multiple board targets
clean core wrappers
clear compatibility matrix
explicit source manifests
upstream cores kept intact where practical
```

Non-goals:

```text
no uncontrolled framework expansion
no hidden build magic
no one-off board forks treated as architecture
no recursive wildcard source discovery as core policy
```

---

## 6. Long-Term Destination

Mistable’s long-term destination is a disciplined, simulation-first FPGA platform where whole-machine cores can be:

```text
developed in simulation
inspected through visible tooling
run through a virtual board
lifted from upstream sources carefully
mapped to physical FPGA hardware later
maintained without board-specific or core-specific sprawl
```

The long-term goal is not merely to clone an existing FPGA ecosystem.

The goal is to build a cleaner, more inspectable, more accessible path for FPGA core development and deployment.

---

## 7. Relationship to Active Work

This roadmap does not select the active task.

A task becomes active only when a human project owner or active prompt names the task/rung file under:

```text
doc/TASKS/
```

This roadmap does not authorize coding agents to implement future phases.

Coding agents must follow:

```text
AGENTS.md
doc/process/agent_workflow.md
doc/TASKS/<active_rung>.md
```

If this roadmap appears to conflict with the master design statement, stop and resolve the conflict explicitly.

Do not silently reinterpret either document.
