# Rung 5 Verification Record: Existing Simulation Spine

Status: Verified  
Role: Formal verification record for Rung 5

---

## 1. Purpose

This document records the formal Rung 5 verification of the existing deterministic simulation spine.

It captures what the current implementation baseline actually proves under the Mistable document-control system.

This is a verification-only record.

It does not design, implement, refactor, migrate, or expand the system.

---

## 2. Authority

This verification record is downstream from:

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
doc/TASKS/rung5.md
```

Active task authority: `doc/TASKS/rung5.md`

Bringup ladder position: Rung 5 — Existing Simulation Spine Verification Record

---

## 3. Repository State

### Branch

```
rung-5-claude
```

### HEAD

```
924a059a3231a843bd2668483b5dcb145cffce5b
```

### Working Tree Status (before verification commands)

```
(clean — no uncommitted changes)
```

Command run:

```bash
git status --short
git rev-parse --abbrev-ref HEAD
git rev-parse HEAD
```

Output:

```
(no output from git status --short — working tree was clean)
rung-5-claude
924a059a3231a843bd2668483b5dcb145cffce5b
```

---

## 4. Commands Run

The following commands were run from the repository root `/work`, which is the expected working directory inside the trusted container.

This environment has Verilator installed directly; no separate `make shell` or Docker invocation was required.

### Command 1: sanity check

```bash
./scripts/sanity.sh
```

### Command 2: smoke verification

```bash
./scripts/test.sh
```

Both commands were run twice. Results were identical on both runs.

---

## 5. Command Results

### scripts/sanity.sh — Full Output

```
------------------------------------------------------------
0) Environment
------------------------------------------------------------
PWD: /work
UID:GID: 1000:1000
USER: cpicker

------------------------------------------------------------
1) Required tools
------------------------------------------------------------
bash:      GNU bash, version 5.1.16(1)-release (x86_64-pc-linux-gnu)
git:       git version 2.34.1
make:      GNU Make 4.3
verilator: Verilator 4.038 2020-07-11 rev v4.036-114-g0cd4a57ad
[sanity] PASS: required tools present

------------------------------------------------------------
2) Repo contract
------------------------------------------------------------
[sanity] PASS: repo contract present

------------------------------------------------------------
3) Write access
------------------------------------------------------------
[sanity] PASS: write access OK

------------------------------------------------------------
4) Git state
------------------------------------------------------------
branch: rung-5-claude
[sanity] PASS: git repo detected

------------------------------------------------------------
5) Verification
------------------------------------------------------------
[test] cleaning previous build output
[test] building simulation
mkdir -p build/vobj
verilator -cc rtl/mistable_top.sv --exe /work/sim/tb.cpp -Mdir build/vobj -o sim
make -C build/vobj -f Vmistable_top.mk
[... Verilator/g++ compilation output ...]
[test] running simulation
[test] artifact sha256: 7985c78be087ba88cfbaca73c538e825632802cdf611c6254f89538ab7f51cc6
[test] PASS: build/frame.ppm generated and matches golden hash
[sanity] PASS: verification passed

[sanity] ALL CHECKS PASSED
```

Result: **PASS**

### scripts/test.sh — Full Output

```
[test] cleaning previous build output
[test] building simulation
mkdir -p build/vobj
verilator -cc rtl/mistable_top.sv --exe /work/sim/tb.cpp -Mdir build/vobj -o sim
make -C build/vobj -f Vmistable_top.mk
[... Verilator/g++ compilation output ...]
[test] running simulation
[test] artifact sha256: 7985c78be087ba88cfbaca73c538e825632802cdf611c6254f89538ab7f51cc6
[test] PASS: build/frame.ppm generated and matches golden hash
```

Result: **PASS**

### Compilation Details (from scripts/test.sh run)

Verilator elaborated `rtl/mistable_top.sv` with `sim/tb.cpp` harness.

g++ compiled and linked the simulation binary to `build/vobj/sim`.

The simulation binary ran and produced `build/frame.ppm`.

---

## 6. Generated Artifact

| Field | Value |
|---|---|
| Artifact path | `build/frame.ppm` |
| Artifact type | Binary PPM image (portable pixmap) |
| Artifact exists after test | Yes |
| File size | 181 KB (185,344 bytes) |
| Observed SHA-256 | `7985c78be087ba88cfbaca73c538e825632802cdf611c6254f89538ab7f51cc6` |
| Expected hash source | `sim/frame.ppm.sha256` |
| Hash match | **Yes — PASS** |

The artifact is not staged or committed. It lives in `build/` which is excluded by `.gitignore`.

---

## 7. Golden Hash Comparison

Expected hash (from `sim/frame.ppm.sha256`):

```
7985c78be087ba88cfbaca73c538e825632802cdf611c6254f89538ab7f51cc6
```

Observed hash (computed by `scripts/test.sh` via `sha256sum`):

```
7985c78be087ba88cfbaca73c538e825632802cdf611c6254f89538ab7f51cc6
```

Result: **Match — PASS**

The golden hash was not updated in this task. `make golden` and `UPDATE_GOLDEN=1 ./scripts/test.sh` were not run.

---

## 8. What This Proves

Under the current Mistable document-control system, the existing simulation spine proves:

```text
implemented
    rtl/mistable_top.sv exists as a minimal RTL top module
    sim/tb.cpp exists as a C++ Verilator simulation harness
    sim/frame.ppm.sha256 exists as a golden checksum for the deterministic artifact

verified
    the Verilator build path works (verilator + make + g++)
    the simulation binary executes without error
    the simulation produces build/frame.ppm as an observable artifact
    the artifact SHA-256 matches the stored golden hash
    scripts/sanity.sh passes all five checks:
        environment (PWD = /work)
        required tools (bash, git, make, verilator)
        repo contract (required files present)
        write access to build/
        verification (scripts/test.sh passes)
    scripts/test.sh passes: build, run, artifact check, hash comparison
    the simulation spine is deterministic at the current golden hash
    the development environment contains the required toolchain
```

---

## 9. What This Does Not Prove

```text
not claimed
    full virtual board behavior
    working monitor or debugger behavior
    bounded service/event transport
    FPGA interaction
    MCU equivalence
    service-link transport
    CORE/ECOSYSTEM/BOARD migration completion
    repository migration into the frozen multi-core structure
    real upstream core support
    NES compatibility
    physical-board readiness
    RP2350 appliance readiness
    Keystone86 PC readiness
    multi-ecosystem support
    multi-board support
    historical task reconciliation
    tuple-aware build system
    monitor console
    virtual board resources (RAM, storage, video, audio, input)
```

Stubs, placeholder files, interface names, and directory structure are not features.

A resource exists only when the active rung defines its scope and a verification record records what passed.

---

## 10. Known Blockers

None observed.

Both acceptance commands passed cleanly.

The golden hash matched on both runs.

No failures were encountered during this verification.

---

## 11. Next Safe Candidate

```text
Rung 6: Repository Structure Migration Planning
```

Per `doc/bringup_ladder.md`, Rung 6 plans how the current minimal/pre-structural repo will move toward the frozen multi-core structure defined in `doc/multi_core_structure.md`.

---

## 12. Final Status

**Verified**

Both `scripts/sanity.sh` and `scripts/test.sh` passed.

The generated artifact `build/frame.ppm` exists and matches the golden hash in `sim/frame.ppm.sha256`.

The existing deterministic simulation spine is verified under the current Mistable document-control system.

Non-claims are preserved as stated in Section 9.

---

## 13. Verification Classification

| Item | Status |
|---|---|
| scripts/sanity.sh | Verified — PASS |
| scripts/test.sh | Verified — PASS |
| build/frame.ppm generated | Verified — exists |
| Golden hash match | Verified — match |
| Full virtual board behavior | Not claimed |
| Monitor/debugger behavior | Not claimed |
| FPGA interaction | Not claimed |
| Real core lift | Not claimed |
| Physical board readiness | Not claimed |
| Tuple structure migration | Not claimed |
