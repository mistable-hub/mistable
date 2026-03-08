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
- NO NETWORK. Analyze ONLY the current directory tree.

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
- NEGATIVE claims (e.g., "no submodules") require explicit filesystem evidence (see Snapshot Proof); otherwise mark **INFERENCE** or **NOT FOUND IN REPO**.
- Forbidden: fake/mangled identifiers (e.g., `staticvoid...`) used as citations or symbols.
- Forbidden: using `NOT_FOUND_IN_SNAPSHOT` as a citation token.

TOOL FALLBACKS (MANDATORY)
- Prefer `rg` for searching. If `rg` is unavailable, use `grep -R -n` with equivalent patterns.
- Prefer git-based proofs if `.git/` exists. If `.git/` is absent (tarball extract), use filesystem-only proof and DO NOT FAIL solely due to missing git metadata.

SELF-REPAIR (MANDATORY)
You MUST complete in ONE RUN by self-repairing predictable failures.
- You may do up to 2 repair passes.
- A repair pass regenerates ONLY the broken artifact(s) (do not rewrite everything).
- After each repair pass, re-run validation.
- Only STOP with FAIL after repair passes are exhausted OR the snapshot is truly incomplete.

======================================================================
PHASE 0 — SNAPSHOT PROOF (MANDATORY FIRST STEP)
======================================================================

Create `docs/repo_snapshot_manifest.md` BEFORE producing any other docs.

It MUST include command outputs (verbatim) for:

1) Snapshot root proof
- `pwd`
- `ls -la` (top-level)

2) Tree proof
- `find . -maxdepth 2 -type d | sort`

3) Tracked-file proof
If `.git/` exists:
- `git rev-parse HEAD`
- `git status --porcelain`
- `git ls-files | wc -l`
- `git ls-files '*.c' | wc -l`
- `git ls-files '*.h' | wc -l`
- `git ls-files '*.S' '*.s' | wc -l`
If `.git/` does NOT exist:
- State: "No .git directory in snapshot; using filesystem-only proof."
- `find . -type f | wc -l`
- `find . -type f -name '*.c' | wc -l`
- `find . -type f -name '*.h' | wc -l`

4) Submodule proof (negative claims must rely on this)
If `.git/` exists:
- `git submodule status --recursive`
Always:
- `find . -maxdepth 2 -name .gitmodules -print`

5) Build system + firmware target proof
- `find . -maxdepth 3 -name Makefile -o -name CMakeLists.txt -o -name '*.mk' -o -name '*.cmake' | sort`
- Identify firmware entrypoints:
  - Prefer: `rg -n "int\\s+main\\s*\\(" .`
  - Fallback: `grep -R -n "int[[:space:]]\\+main[[:space:]]*(" .`
- Identify startup/entry files if present:
  - Prefer: `rg -n "(Reset_Handler|startup|ENTRY\\()|\\bvector\\b" . | head -n 100`
  - Fallback: `grep -R -n -E "(Reset_Handler|startup|ENTRY\\()|\\bvector\\b" . | head -n 100`

6) No-network statement
- "No network access used; analysis limited to current directory tree."

PHASE 0 GATE (MANDATORY)
Proceed only if:
- You can enumerate tree + build system files + likely entrypoints (or explicitly state NOT FOUND IN REPO), AND
- You have produced submodule proof, AND
- You confirm you are analyzing ONLY the current directory tree.

If snapshot appears incomplete in a way that blocks extraction, mark FAIL (but only after attempting available fallbacks).

======================================================================
PHASE 1 — MECHANICAL MODULE INVENTORY (MANDATORY, NO HALLUCINATION)
======================================================================

Create:
1) `docs/module_inventory.csv`
2) `docs/inventory_warnings.md`

`docs/module_inventory.csv` MUST be mechanical (no guessed APIs).
Columns:
- file_path
- kind (c/h/S/ld/mk/other)
- includes (first 10 `#include` lines if present; else blank)
- exports (for .h: matched lines for `extern`, `typedef`, `struct`, `enum`, `#define` — first 50 matches; else blank)
- defs (for .c: top-level function definitions detected by conservative regex — first 50 matches; else blank)

Rules:
- Do NOT invent symbol names.
- Do NOT output mangled tokens.
- If extraction fails for a file, leave fields blank and log in `docs/inventory_warnings.md`.

======================================================================
REPO STUDY INSTRUCTIONS (MANDATORY)
======================================================================
1) Enumerate all source modules (*.c/*.h) and summarize each module’s responsibility (use mechanical inventory + evidence; no guessing).
2) Identify top-level control flow and sequencing (entrypoints, main loop, ISR-driven flows).
3) Extract the service model S1..S5 (state machines + error handling).
4) Extract the MCU<->FPGA contract exactly as implemented, including byte-level framing.
5) Extract implicit user-facing contracts (menu flow, file search order, defaults, config handling).
6) Identify hardware abstraction points (STM32/peripheral usage) as an abstract driver surface only.

======================================================================
DELIVERABLES (MANDATORY)
======================================================================

1) Create `docs/cleanroom_port_spec.md` with these sections:

A. System Overview
- OBSERVED: High-level control-plane behavior only
- OBSERVED: External interfaces: SD, USB/input, FPGA link, OSD
- OBSERVED: Explicit boundary between MCU and FPGA responsibilities
- OBSERVED/INFERENCE: Any boot sequence and initialization ordering

B. Module Inventory (Repo-wide)
- Table: file -> responsibility (1–3 sentences) -> key public APIs -> evidence
- Include all modules, even if trivial.
- IMPORTANT: derive “key public APIs” ONLY from real symbols in headers / defs from inventory; do NOT invent.
- If uncertain: NOT FOUND IN REPO.

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

J. Open Items (Strict)
- List any NOT FOUND IN REPO items that block faithful implementation.
- For each open item: impact + minimum evidence needed.

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

======================================================================
PHASE 3 — VALIDATION + SELF-REPAIR (MANDATORY)
======================================================================

Create `docs/validation_report.md` and validate:

A) Citation integrity checks (FAIL if any):
- Scan `docs/cleanroom_port_spec.md` and `docs/evidence_index.md` for forbidden tokens:
  - `NOT_FOUND_IN_SNAPSHOT`
  - mangled identifiers like `staticvoid`
- Verify every evidence citation references an existing file path.
- For citations that include `:symbol()`:
  - Verify the symbol string appears in the referenced file (simple text match is acceptable).
  - If not verifiable, mark FAIL and list offending rows.

B) Coverage checks (FAIL if any):
- Every MUST MATCH claim bullet in the spec has a corresponding row in `docs/evidence_index.md`.
- Every wire-format example has at least one citation.

C) Snapshot proof checks:
- Confirm `docs/repo_snapshot_manifest.md` exists and includes required command outputs.

D) Self-repair loop:
If FAIL:
- Regenerate ONLY the broken artifact(s) to resolve the specific failures.
- Re-run validation.
- Up to 2 repair passes.
- If still FAIL after repairs, stop and report FAIL with exact blockers.

STOP CONDITION
- PASS: stop after docs exist and validation passes.
- FAIL: stop only after repair passes exhausted.
- Do NOT proceed to writing RP2350 code.
- Do NOT propose enhancements or future features.