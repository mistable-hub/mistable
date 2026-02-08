# Task 001 — Container-First Runner (Always Docker)

## Status
Frozen once committed. Do not modify after acceptance.

---

## Goal
Make `./scripts/test.sh` run **always** inside a deterministic Docker tool-room, so execution is identical across machines and environments.

This task must not change the RTL behavior or simulation outputs. It only changes how the build/test is executed.

---

## Definition of Done (Authoritative)

Running:

```bash
./scripts/test.sh
```

must:

- build (or reuse) the Docker image locally
- run the build + simulation **inside Docker**
- exit with status code `0`
- produce the file `build/frame.ppm` in the host working tree

---

## Constraints

- `./scripts/test.sh` must **always** use Docker (no native-tool fallback).
- No CI files added.
- No additional build systems (FuseSoC, CMake, Bazel, Meson, etc.).
- No GUI, SDL, or windowing dependencies.
- Keep changes minimal and legible.
- Only the following files may be changed or created:
  - Create: `scripts/docker.sh`
  - Modify: `scripts/test.sh`

No other files may be edited for this task.

---

## Required Changes

### Create File: `scripts/docker.sh`

#### Purpose
Provide a single wrapper to run arbitrary commands inside the Docker tool-room with the repository mounted.

#### Requirements

- Must be executable.
- Must determine the repository root by locating `AGENTS.md`.
- Must mount the repository root to `/work` inside the container.
- Must set the working directory to `/work`.
- Must ensure the Docker image exists, building it if missing.
- Must pass through stdout, stderr, and exit codes unchanged.
- Must avoid creating root-owned files on the host when feasible by mapping the host user.

#### Fixed Image Details

- Image tag: `mistable-dev`
- Dockerfile path: `container/Dockerfile`

#### Image Existence Check (Authoritative)

To determine whether the image exists, run:

```bash
docker image inspect mistable-dev >/dev/null 2>&1
```

If this command fails, build the image using:

```bash
docker build -t mistable-dev -f container/Dockerfile .
```

No other logic is permitted.

#### Container Execution (Authoritative)

Commands must be executed using:

- mount: `-v "<repo_root>:/work"`
- workdir: `-w /work`
- shell: `bash -lc "<command>"`

User mapping:

- Prefer running as the host user using:
  ```bash
  -u "$(id -u):$(id -g)"
  ```
- If user mapping fails, fall back to the container default user and print a warning to stderr.

TTY handling:

- Use `-it` only if stdout is a TTY.

#### Interface

`scripts/docker.sh` must support:

```bash
./scripts/docker.sh <command...>
```

Examples:

```bash
./scripts/docker.sh make sim
./scripts/docker.sh echo hello
```

If no command is provided, print usage and exit non-zero.

The exit code must be the exit code of the command executed inside Docker.

---

### Modify File: `scripts/test.sh`

#### Purpose
Provide the single authoritative entry point for verification. All build and simulation steps must execute inside Docker.

#### Requirements

- Must be executable.
- Must fail immediately on any error.
- Must not execute Verilator, Make, or other build tools on the host.
- Must use `scripts/docker.sh` for all build and simulation work.

#### Required Steps (Exact Order)

1. Remove the `build/` directory if it exists.
2. Invoke the Docker wrapper to run the simulation build:
   ```bash
   ./scripts/docker.sh make sim
   ```
3. Verify that `build/frame.ppm` exists and is non-empty.
4. Print a success message containing the string `PASS`.
5. Exit with status code `0`.

If any step fails, exit non-zero.

---

## Verification Procedure (Executor)

1. Run:

```bash
./scripts/test.sh
```

2. Confirm:
- exit code is `0`
- `build/frame.ppm` exists on the host filesystem
- output contains `PASS`

3. Run the command a second time to confirm the Docker image is reused and the result is identical.

4. Stop. Do not refactor, extend, or generalize.

---

## Explicit Non-Goals

Do **not** add or introduce:

- additional scripts beyond `scripts/docker.sh`
- new Docker images
- CI pipelines or configuration
- synthesis or P&R tooling
- board support packages
- NES or other console cores
- abstraction layers or future-oriented architecture
