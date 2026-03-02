YOU ARE CODEX.

MISSION
Study the MiST firmware repository in its complete state and produce a CLEAN-ROOM PORTING SPEC that is sufficient to re-implement the firmware behavior on RP2350 + FreeRTOS WITHOUT copying code.

The goal is behavioral compatibility, not source compatibility.

HARD RULES
- Do NOT implement code.
- Do NOT copy/paste code (no large snippets).
- Do NOT redesign architecture.
- Do NOT add features.
- Do NOT guess missing info.
- Do NOT propose improvements.
- Do NOT generalize beyond what exists.
- Every statement must be supported by evidence from the repo.

COMPATIBILITY BUDGET (MANDATORY)
Classify all behaviors into one of the following categories:

MUST MATCH
- FPGA link protocol behavior
- ROM loading semantics and handshakes
- OSD update semantics and memory model
- Core control/reset behavior
- User-visible menu flow and file selection logic
- Error reporting semantics visible to user or FPGA
- FPGA link wire format (byte-level framing)

MAY DIFFER
- Internal scheduling model
- STM32 peripheral usage
- Blocking vs event-driven implementation
- RTOS structure
- Exact menu rendering implementation details (visual style), as long as flows and semantics match
- Low-level driver implementation

DO NOT expand beyond the MUST MATCH scope.
DO NOT introduce features or compatibility goals not present in MiST firmware.

EVIDENCE REQUIREMENT (MANDATORY)
- Every behavior bullet in the spec MUST begin with either **OBSERVED** or **INFERENCE**.
  - **OBSERVED**: requires direct evidence citations.
  - **INFERENCE**: requires supporting evidence citations + a short justification explaining why the inference follows.
- Every bullet in the spec MUST include at least one citation in the form:
  `path/to/file.c:function()` or `path/to/file.h:symbol`
- If evidence cannot be found, explicitly state: **NOT FOUND IN REPO** (and do not speculate).

REPO CONTEXT CONFIRMATION (MANDATORY FIRST STEP)
Before producing any docs:
1) Print the repo root path you are using.
2) List the full top-level tree (at least: top-level dirs + key src/include dirs).
3) Identify the firmware target(s) present (e.g., main entrypoint file(s), build system files, and any target/board selection).
4) Confirm you are analyzing the complete repository state that is available in your environment (including submodules if present). If submodules are missing/uninitialized, say so explicitly.

REPO STUDY INSTRUCTIONS (MANDATORY)
1) Enumerate all source modules (*.c/*.h) and summarize each module’s responsibility.
2) Identify top-level control flow and sequencing (entrypoints, main loop, any ISR-driven flows).
3) Extract the service model S1..S5 as described below, including state machines and error handling.
4) Extract the MCU<->FPGA contract exactly as implemented, including byte-level framing.
5) Extract all implicit user-facing contracts (menu flow, file search order, defaults, config handling).
6) Identify hardware abstraction points (STM32/peripheral usage) as an abstract driver surface only.

DELIVERABLES

1) Create `docs/cleanroom_port_spec.md` with these sections:

A. System Overview
- OBSERVED: High-level control-plane behavior only
- OBSERVED: External interfaces: SD, USB/input, FPGA link, OSD
- OBSERVED: Explicit boundary between MCU and FPGA responsibilities
- OBSERVED/INFERENCE: Any boot sequence and initialization ordering

B. Module Inventory (Repo-wide)
- Table: file -> responsibility (1–3 sentences) -> key public APIs -> evidence
- Include all modules, even if trivial.

C. Service Model (S1..S5)

S1 FPGA Link / Control
S2 OSD + Menu Rendering (content producer)
S3 SD/FAT Storage + File Browser
S4 Input Aggregation (USB HID -> menu/core events)
S5 Config Persistence

For each service:
- Responsibilities
- Inputs/Outputs
- Owned state (globals/structs)
- Public API surface (functions + structs/enums)
- State machine (text diagram)
- Error handling patterns (return codes, retries, user messages)
- Timing assumptions (polling loops, delays, blocking calls)
- MUST MATCH vs MAY DIFFER classification per behavior bullet (with OBSERVED/INFERENCE tags)

D. FPGA Link Contract (Semantic)
- Transport details (SPI framing, timing assumptions)
- Register map / command codes as implemented
- ROM loading path (chunking, handshake, busy/ready behavior)
- OSD update path (tile/palette/commands)
- Core control operations (reset/select/status)
- Any CRC/retry behavior
- Explicit timing or blocking assumptions (delays, retries, timeouts)
- MUST MATCH vs MAY DIFFER classification per behavior bullet

E. File/Path Contract (User-facing + Loader-facing)
- Default directories searched
- File extension filters (per menu context / core context)
- Config file names and locations
- Boot-time search order and fallbacks
- Any filename parsing, sorting, “last used” persistence behavior
- MUST MATCH vs MAY DIFFER classification per behavior bullet

F. User-visible UX Contract
- Menu flow and screens (state machine)
- Directory navigation logic
- File selection rules
- Progress reporting + update cadence (if present)
- Error messages and recovery behavior (what user sees, what triggers it)
- Default behaviors on boot
- MUST MATCH vs MAY DIFFER classification per behavior bullet

G. FPGA Link Wire Format (Byte-level, MUST MATCH)
This section must be exact enough that an independent implementation can interoperate.
Include:
- SPI transaction framing for:
  - register read
  - register write
  - burst write (ROM streaming)
  - any special command modes
- Address width, endianness, alignment assumptions
- Chip-select usage assumptions (per-transaction, continuous burst, etc.)
- Maximum burst sizes used in practice (as implemented)
- Busy/ready polling behavior (status reads, required delays, timeouts)
- Any required inter-byte or inter-transaction delays
- For EACH SPI operation type, provide at least one explicit example frame as hex bytes,
  using placeholders where necessary (e.g., AA for address bytes, DD for data bytes).
  If exact bytes cannot be derived from the repo, mark that sub-item: NOT FOUND IN REPO.
- MUST MATCH vs MAY DIFFER classification per behavior bullet

H. Hardware Abstraction Points
- List all STM32/peripheral dependencies
- Show where they appear in code
- Identify required portable driver APIs (surface only, no implementation):
  - SPI
  - SD/FAT
  - USB/HID
  - Timers
  - GPIO
  - Optional: UART/logging (only if used)
- For each driver API, list required behaviors (blocking, async, callbacks) as OBSERVED/INFERENCE

I. Clean-room RTOS Mapping Notes (STRICTLY LIMITED)
- Recommend max 4 tasks
- Enforce single-owner rule for FPGA bus (one task owns SPI)
- Suggested queues/events (names and payloads)
- Explicitly state what MUST remain single-threaded
- Include a "Responsiveness Budget" subsection:
  - menu input latency targets (extract from code if present, otherwise NOT FOUND IN REPO)
  - OSD refresh/progress update cadence (extract if present, otherwise NOT FOUND IN REPO)
  - ROM streaming chunk cadence / polling delays (extract if present, otherwise NOT FOUND IN REPO)
- No new features
- No architectural redesign
- No implementation details beyond task/queue ownership

2) Create `docs/evidence_index.md`
- Table format (one row per claim, not per section):
  - Spec section
  - Claim summary
  - Classification (MUST MATCH / MAY DIFFER)
  - Tag (OBSERVED / INFERENCE)
  - Evidence citation(s)

QUALITY BAR (MANDATORY)
- The spec must be sufficiently precise that an engineer can implement the RP2350+FreeRTOS firmware without reading MiST source code again.
- Any ambiguity must be called out explicitly with NOT FOUND IN REPO, rather than guessed.

STOP CONDITION
- When both documents exist and are internally consistent.
- Do NOT proceed to writing RP2350 code.
- Do NOT propose enhancements or future features.