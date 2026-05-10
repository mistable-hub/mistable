# Mistable Master Design Statement

Status: Baseline v0.1  
Role: Root design identity and non-negotiable project intent

---

## 1. Purpose

Mistable is a simulation-first, MiSTer-inspired FPGA platform designed to make FPGA development more accessible, inspectable, portable, and disciplined.

Mistable exists to let FPGA-style systems be developed, simulated, inspected, and eventually mapped to real hardware without requiring physical FPGA bring-up as the first step.

The project should make it possible to move whole-machine cores through the development path:

```text
simulation
    → virtual board
        → real FPGA board
```

Whole-machine cores are not the final stage of the path. They are the systems carried through the path: first developed and inspected in simulation, then exercised on the virtual board, and eventually mapped to real FPGA hardware without losing structure, portability, or clarity.

---

## 2. Root Design Intent

Mistable is not just a collection of cores.

Mistable is a platform for hosting FPGA cores behind clear board, ecosystem, and build boundaries.

A Mistable core may be a small logic block, but it may also be a complete machine.

Examples of whole-machine cores include:

```text
NES-compatible system
PC-compatible system
arcade board
console
computer
custom FPGA appliance
```

A whole-machine core may include:

```text
CPU
chipset
video subsystem
audio subsystem
input subsystem
storage/media interface
ROM/BIOS integration
internal buses
timers/interrupt logic
debug/status hooks
```

Mistable must support this model without making the platform itself specific to any one machine.

---

## 3. Non-Negotiable Principles

### 3.1 Simulation First

Mistable development begins in simulation.

A core, board contract, or platform feature should be proven in a deterministic simulation path before being treated as portable or hardware-ready.

Simulation is not a side path. It is the first-class bring-up path.

### 3.2 Concrete Before Generic

Mistable should build working concrete targets before creating broad abstractions.

Do not create a generic framework, plugin system, HAL, or multi-board abstraction before there is working behavior that justifies it.

Abstraction must be earned by repeated working cases.

### 3.3 Whole-Machine Cores Are Valid Cores

Mistable cores may represent full systems, not only isolated CPU blocks.

A PC-compatible core, for example, should be packaged as a core that contains the CPU plus PC-compatible chipset RTL and machine-specific logic.

Mistable must provide generic platform resources, but it must not absorb machine-specific chipset behavior into the platform layer.

### 3.4 Platform Resources Stay Generic

Mistable may provide generic board/platform resources such as:

```text
clock/reset
fast RAM / working memory
large storage / media
video output
audio output
keyboard / mouse / joystick input
service/debug/monitor paths
build and simulation control
```

Mistable must not become:

```text
NES-specific
PC-specific
MiSTer-specific
RP2350-specific
single-board-specific
single-core-specific
```

Machine-specific behavior belongs inside the core or core integration layer.

### 3.5 Upstream Cores Stay Intact

When importing upstream FPGA cores, upstream source should remain intact where practical.

Local integration should happen through wrappers, adapters, manifests, and documented integration files.

Do not fork or rewrite upstream cores casually.

Do not bury board-specific or ecosystem-specific assumptions inside upstream core source.

### 3.6 Make and Docker Are the Visible Control Path

Make is the visible build/control plane.

Docker is the stable development environment.

The project should avoid hidden magic. Important operations should be visible through explicit commands.

Scripts may support the workflow, but they must not hide major behavior that belongs in Make or documented task flow.

### 3.7 Accessibility Is a Core Goal

Mistable should make FPGA work understandable to users who are not already experts in RTL, simulators, waveform viewers, or hardware bring-up.

The project should prefer visible, inspectable behavior.

Users should be able to interact with the system through normal developer tools such as:

```text
make
Docker
terminal monitor
logs
generated artifacts
deterministic tests
```

A user should not need a physical FPGA board before they can see meaningful behavior.

---

## 4. Virtual Board Intent

The virtual board is the first accessibility and development target.

Its purpose is to let cores and board behavior run in a Linux-hosted environment before physical FPGA hardware is required.

The virtual board is expected to grow toward host-backed versions of board resources, as authorized by the roadmap and bring-up ladder:

```text
RAM model
storage image
video output
audio output
input mapping
service/debug/monitor console
bounded event paths
```

The virtual board must not become a separate architecture that conflicts with the physical board path.

The virtual board and physical board should be different implementations of the same platform concepts.

### 4.1 Working Virtual Board Proof Gates

The virtual board is not considered working merely because the repository contains abstractions, interfaces, or planned resource names.

A working virtual board must prove visible behavior through the ordered bring-up ladder.

At minimum, before being treated as a working virtual board, the project must demonstrate:

```text
deterministic build/run path
observable simulation output or artifact
human-facing monitor/status path
bounded reset/status/event behavior
at least one concrete core or demo target using the board path
clear non-claims for resources not yet implemented
```

Additional board resources such as RAM, storage, video, audio, input, and service/debug transport become real only when the active rung defines their scope and verification records what passed.

The virtual board must not claim a resource exists merely because a stub, interface name, or placeholder file exists.

---

## 5. Service / Monitor Intent

Mistable should provide a human-facing monitor/debug path.

In simulation, this may be a terminal monitor.

On real hardware, this may map to a serial console, USB CDC console, MCU monitor, or similar service interface.

The monitor exists to make the system observable and approachable.

The monitor may grow toward capabilities such as:

```text
status
reset
events
help
color output
no-color mode
storage/media status
input status
trace controls
debug hooks
```

The monitor must not become an unbounded real-time dependency.

Human-facing output may be rich and formatted, but FPGA-facing communication must remain bounded, explicit, and controlled.

### 5.1 Minimum Working Monitor Proof Gates

The monitor is not considered working merely because a command shell, stub, or placeholder script exists.

A minimum working monitor must prove visible, repeatable behavior through the ordered bring-up ladder.

At minimum, before being treated as a working monitor, the project must demonstrate:

```text
launch path through documented Make or script command
human-readable status output
help or command-discovery output
clear indication of attached, stubbed, or unavailable board/core state
bounded event/status reporting model
color output policy with a no-color path for logs or unsupported terminals
non-interactive smoke path suitable for automated verification
clear non-claims for debugger, service-link, or hardware behavior not yet implemented
```

The monitor must not claim FPGA interaction, MCU equivalence, service-link behavior, or debugger capability merely because the user interface exists.

Monitor capabilities become real only when the active rung defines their scope and verification records what passed.

---

## 6. Board / Core Boundary

Mistable must preserve a clean boundary between the platform and cores.

The platform may provide generic resources.

The core owns machine-specific behavior.

For example:

```text
Mistable platform:
    provides generic RAM, storage, video, audio, input, service/debug paths

NES core:
    owns NES CPU/PPU/APU/cartridge/controller behavior

PC-compatible core:
    owns CPU, chipset, BIOS integration, timers, interrupt logic, VGA/CGA/etc.

RP2350 appliance:
    may implement a physical service/control path for a real board
```

The platform must not become the machine.

The core must not depend on hidden host behavior.

---

## 7. Document System and Authority Roles

Mistable uses a coordinated document system. Each document type has one job and must not silently duplicate, replace, or redefine another document’s job.

This document system exists to combine modern development discipline with AI coding-agent workflows. It should make coding agents behave like bounded developer team members, not autonomous architects.

This document is the root design identity for Mistable.

This document does not require ratification from any other document. It is the root design statement. Lower-level documents may refine, sequence, apply, or verify this design intent, but they must not redefine it silently.

The authority roles are:

```text
doc/master_design_statement.md
    Root identity.
    Defines what Mistable is and must remain.
    This is the highest-level design intent document.

doc/ROADMAP.md
    Big-picture development phases.
    Defines where Mistable goes over time.
    Does not authorize current implementation by itself.

doc/bringup_ladder.md
    Ordered proof rungs.
    Defines what order work happens in and what must be proven before the next rung.
    Does not replace active task/rung files.

doc/TASKS/task_template.md
    Standard developer-directive shape.
    Defines how task/rung files are written.
    Does not authorize implementation by itself.

doc/TASKS/<active_rung>.md
    Current developer directive.
    Defines what is authorized now.
    Defines allowed files, blocked scope, acceptance commands, and explicit non-claims.

doc/process/agent_workflow.md
    Agent session procedure.
    Defines how ChatGPT, Claude Code, Codex, or similar agents execute work:
        classify,
        implement only authorized scope,
        review dirty diffs,
        verify,
        report.

doc/process/code_review.md
    Review procedure.
    Defines how changes are reviewed.
    Review is read-only unless explicitly authorized.

doc/source_of_truth.md
    Current repo truth map.
    Defines which files currently own which project facts, build paths, generated artifacts, and implementation surfaces.

doc/VERIFICATION/<rung>.md
    Proof record.
    Records what actually passed, what is proven, and what remains unclaimed.
    Created or updated only when verification evidence exists.
```

This document does not replace the existing architecture and process documents.

Repository structure and long-term integration policy are defined by:

```text
doc/multi_core_structure.md
```

Simulation-first core lift rules are defined by:

```text
doc/core_lift_sim_contract.md
```

Task-specific work is defined by files under:

```text
doc/TASKS/
```

Future roadmap and bring-up sequencing should be defined by:

```text
doc/ROADMAP.md
doc/bringup_ladder.md
```

Agent/process behavior should be defined by:

```text
AGENTS.md
doc/process/
```

If this document appears to conflict with a lower-level document, stop and resolve the conflict explicitly. Do not silently reinterpret either document.

---

## 8. Relationship to Keystone86

Keystone86 is a separate CPU / PC-compatible machine effort.

Mistable may eventually host a Keystone86-based whole-machine PC core, but Mistable itself must not become Keystone86-specific.

The intended long-term relationship is:

```text
keystone86
    CPU implementation

keystone86_pc
    whole-machine PC-compatible core package

mistable
    platform / board / ecosystem host

virtual board
    first simulation and accessibility target for development
```

Before attempting a Keystone86 PC core inside Mistable, Mistable should prove the platform path using smaller and more approachable targets.

The first real-core target and sequencing constraints belong in:

```text
doc/ROADMAP.md
doc/bringup_ladder.md
```

This master design statement permits a smaller first real-core target, such as a NES core lift, but the exact sequence must be controlled by the roadmap and bring-up ladder rather than this section.

---

## 9. Development Philosophy

Mistable should be developed through small, intentional rungs.

Each rung should define:

```text
what it proves
what it does not prove
what files may change
what files must not change
what commands prove success
what remains explicitly unclaimed
```

Do not advance the platform by broad inference.

Do not start future-rung work just because it seems useful.

If a feature is not authorized by the active task or rung, it is out of scope.

### 9.1 Rung Validity and Invalidation

A rung is valid only to the extent that its recorded verification remains true.

A rung may be invalidated if later evidence shows that:

```text
the required acceptance command did not actually pass
the wrong files or branch were tested
the implementation exceeded the authorized scope
a protected document was modified without authorization
the verification record overclaimed what was proven
a later regression contradicts the claimed behavior
```

If a rung is invalidated, future work depending on that rung must stop until the invalidation is resolved.

Resolution may require:

```text
fixing the implementation
narrowing the claim
updating the verification record
creating a corrective rung
rerunning acceptance commands
```

Do not silently continue building on an invalidated rung.

---

## 10. AI Coding-Agent Philosophy

Coding agents are contributors, not architects.

They execute committed developer directives.

They must not infer project direction from chat history, prior sessions, or unstated intent.

The project should use written files to control agent work:

```text
master design statement
roadmap
bringup ladder
task template
active task/rung directive
agent workflow
review checklist
source-of-truth map
verification records
```

ChatGPT or another reasoning system may help design the next rung, but the coding agent should execute only the committed active directive.

Repo files and Git history are authority.

Agent memory is not authority.

Coding agents must operate inside the current task/rung system. They may report concerns, blockers, or conflicts, but they must not resolve those conflicts by inventing architecture or expanding scope.

### 10.1 Agent Handoff and Session State

Agent handoff must be explicit.

When an agent session ends, the project should preserve enough state for a future agent or human to understand:

```text
what was attempted
what changed
what commands were run
what passed
what failed
what remains incomplete
what must be verified before proceeding
```

The exact handoff format belongs in:

```text
doc/process/agent_workflow.md
```

A new agent session must not rely on previous chat/session memory as authority. It must recover state from committed files, Git status, task/rung files, verification records, and any explicit handoff artifact defined by the process docs.

### 10.2 Agent Reporting

Coding agents must report work in a structured form defined by the active task and process documents.

At minimum, reports should make clear:

```text
current branch
current HEAD
working tree status
files changed
commands run
pass/fail result
implemented scope
non-claims
blockers or concerns
next safe candidate
```

The exact reporting template belongs in:

```text
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/<active_rung>.md
```

Do not treat an unstructured narrative summary as sufficient proof of completion.

### 10.3 Parallel Agent Policy

Mistable assumes one active implementation agent per branch and active rung unless explicitly authorized otherwise.

Do not run multiple coding agents against the same branch/rung at the same time unless the active task or human project owner explicitly defines how conflicts will be avoided.

Parallel reasoning or review is allowed only when it does not create competing uncoordinated edits.

If multiple agents produce conflicting recommendations, the conflict must be resolved in written repo authority before implementation proceeds.

### 10.4 Tool and Capability Boundaries

Agent capability must be controlled by task and process authority.

The right to read files, edit files, run shell commands, run tests, create commits, push branches, modify protected files, or perform review-only work must be defined by:

```text
AGENTS.md
doc/process/agent_workflow.md
doc/process/code_review.md
doc/TASKS/<active_rung>.md
```

A coding agent with broad tool access is not automatically authorized to use that access.

Tool availability is not permission.

If a task is review-only, the agent must not edit files.

If a task does not authorize commits or pushes, the agent must not commit or push.

If a task does not authorize protected-file edits, the agent must stop and report the need rather than editing them.

---

## 11. What Mistable Must Not Become

Mistable must not become:

```text
a one-off NES port
a one-off PC clone
a one-off RP2350 appliance
a pile of board-specific hacks
a generic framework with no working concrete target
a rewrite of upstream cores
a hidden build system
a project that requires physical FPGA hardware before meaningful progress is visible
```

Mistable must remain a disciplined, simulation-first platform for building, lifting, testing, and eventually deploying FPGA whole-machine cores.

---

## 12. One-Sentence Summary

Mistable is a simulation-first, MiSTer-inspired FPGA platform for accessible whole-machine core development, built around clear boundaries, deterministic bring-up, visible tooling, and a virtual board path that can later map to real FPGA hardware.
