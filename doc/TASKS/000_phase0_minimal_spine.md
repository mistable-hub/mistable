# Task 000 — Phase 0 Minimal Spine

## Status
Frozen once committed. Do not modify after acceptance.

---

## Goal
Bootstrap the smallest possible working system that:

- builds and runs a Verilator simulation
- produces a real, inspectable artifact
- proves the development toolchain and repository spine work

This task intentionally avoids frameworks, catalogs, abstraction layers,
or long-term architecture decisions.

---

## Definition of Done (Authoritative)

This task is complete **only if** the following command:

```bash
./scripts/test.sh
```

- exits with status code `0`
- produces the file `build/frame.ppm`

No other criteria matter for completion.

---

## Required Repository Structure

Create exactly the following files and directories:

```
mistable/
  container/
    Dockerfile
  rtl/
    mistable_top.sv
  sim/
    tb.cpp
  scripts/
    test.sh
  Makefile
  .gitignore
  README.md
```

No additional tooling, frameworks, build systems, or directories are allowed.

---

## Tooling Constraints

### Docker (Minimal Tool Room)

- Base image: `ubuntu:22.04`
- Installed packages:
  - ca-certificates
  - git
  - build-essential
  - make
  - verilator
- No yosys, nextpnr, or synthesis tools
- No GUI, windowing, or SDL dependencies

The Docker image must be sufficient to run `./scripts/test.sh`.

---

## RTL Requirements

### File: `rtl/mistable_top.sv`

#### Module Interface

- Module name: `mistable_top`
- Parameters:
  - `W = 256`
  - `H = 240`
- Inputs:
  - `clk`
  - `rst`
- Outputs:
  - `pix_valid`
  - `pix_r[7:0]`
  - `pix_g[7:0]`
  - `pix_b[7:0]`
  - `pix_x[15:0]`
  - `pix_y[15:0]`
  - `frame_done`

#### Behavior

- Implements a simple raster scan over `(x, y)`
- Asserts `pix_valid` during active pixel output
- Pulses `frame_done` once per full frame
- Generates a deterministic test pattern:
  - 8 vertical color bars across the width
  - the final bar is a gradient

Functional correctness is sufficient; no real video timing accuracy is required.

---

## Simulation Requirements

### File: `sim/tb.cpp`

- Uses the Verilator-generated C++ model
- Drives clock and reset
- Captures the pixel stream into a framebuffer
- Stops simulation when `frame_done` is observed
- Writes `build/frame.ppm` in **PPM P6** format
- Returns a non-zero exit code if `frame_done` is never observed

No GUI, windowing, or SDL libraries are permitted.

---

## Build System Requirements

### File: `Makefile`

- Provides a target named `sim`
- Uses Verilator to:
  - compile `rtl/mistable_top.sv`
  - link with `sim/tb.cpp`
- Build output directory: `build/vobj`
- Running the built simulation must generate `build/frame.ppm`

---

## Script Requirements

### File: `scripts/test.sh`

- Must be executable
- Must perform the following steps:
  1. clean any previous build output
  2. build the simulation
  3. run the simulation
  4. verify that `build/frame.ppm` exists
  5. print a success message

This script is the **only supported entry point** for verification.

---

## Documentation Requirements

### File: `README.md`

Must include:

- Instructions for running `./scripts/test.sh` on the host
- Instructions for building and running via Docker:

```bash
docker build -t mistable-dev -f container/Dockerfile .
docker run --rm -it -v "$PWD:/work" -w /work mistable-dev ./scripts/test.sh
```

- A brief description of the `build/frame.ppm` output artifact

---

## Explicit Non-Goals (Phase 0)

Do **not** add or introduce:

- NES core logic
- FuseSoC
- CI pipelines
- core catalogs
- board support packages
- synthesis or place-and-route flows
- abstraction layers or hardware interfaces

These belong to later tasks.

---

## Completion Instructions (For Executor)

1. Create all required files exactly as specified.
2. Run `./scripts/test.sh`.
3. Fix issues until the command passes.
4. Stop. Do not extend or refactor beyond this task.

