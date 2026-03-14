# Multi-Core, Multi-Ecosystem, and Upstream Core Integration Structure

**Status:** Frozen architectural policy/spec for repository structure and integration boundaries.

This document defines the recommended repository structure and integration model for growing `mistable` into a disciplined, portable, forward-looking project that can host cores across multiple ecosystems without turning into a tangled set of one-off ports.

This document is intentionally written as a **policy/spec**, not as an open-ended brainstorming note.

Once adopted, it should be treated as the frozen structural baseline for the repository. It should only be revised when a real implementation exposes a boundary flaw, a naming conflict, a build/control ownership problem, or an upstream integration issue that this structure cannot cleanly represent.

The structure is designed to support:

- `mist`
- `mister`
- `mistex`
- `analogue-pocket`
- future `mistable`-native environments

The primary goals are:

- keep the build system explicit and readable
- separate framework logic from core logic
- separate ecosystem adaptation from board realization
- separate reusable logic from board-specific glue
- allow importing known-good upstream cores such as NES
- preserve a clean upgrade path from upstream authors
- avoid hidden or magical build behavior
- keep the structure compatible with a future FuseSoC or similar metadata layer if desired
- prevent the repository from exploding into duplicated per-core, per-ecosystem forks

---

## Design Principles

This structure is based on a small number of rules.

### 1. Keep boundaries visible

There are five major layers:

- framework
- core
- ecosystem
- board
- build/control

Each layer should have a clear job and should not absorb responsibilities from the others.

### 2. Keep upstream code intact whenever possible

Third-party cores should be imported as dependencies, not rewritten into the project tree. Repo-specific glue should live outside the upstream code.

### 3. Makefiles own the control plane

Makefiles should declare:

- what is being built
- which sources are used
- which core is selected
- which ecosystem is selected
- which board is selected
- what artifact is produced

Shell scripts should be thin convenience wrappers, not second build systems.

### 4. Board directories should stay small

A board directory should contain only board-specific items such as:

- board `Makefile` or `board.mk`
- optional `build.sh`
- constraint files
- PLL / clock wrapper
- board top file

It should not become a dumping ground for reusable logic.

### 5. Ecosystem logic must stay out of the core wrapper

A core wrapper should adapt an upstream core to the stable `mistable` framework contract.

It should **not** become a place where MiST, MiSTer, MiSTeX, and Analogue Pocket assumptions are all mixed together.

### 6. Upstream update path must remain clean

The project should be able to update third-party cores intentionally and reviewably, without losing local integration work.

### 7. Portability is achieved by changing adapters, not cloning cores

A core should be portable by changing:

- selected ecosystem
- selected board

It should **not** require duplicating the core integration into:

- `nes_mist`
- `nes_mister`
- `nes_mistex`
- `nes_pocket`

That is exactly the kind of structure explosion this model is meant to prevent.

### 8. The compatibility matrix is constrained, not fully Cartesian

Not every combination of:

- core
- ecosystem
- board

will be legal or meaningful.

This architecture should **not** promise that every `CORE × ECOSYSTEM × BOARD` combination exists.

Instead, the build system should explicitly validate supported tuples.

Examples of valid patterns may include:

- `CORE=nes ECOSYSTEM=sim BOARD=sim`
- `CORE=nes ECOSYSTEM=mister BOARD=de10-nano`

Examples of combinations that may be invalid or unsupported include:

- `CORE=nes ECOSYSTEM=analogue-pocket BOARD=icepi-zero`

This is a strength, not a weakness. It keeps the architecture honest and prevents fake portability.

### 9. The framework must stay narrow and boring

The framework is the stable internal integration contract of `mistable`.

It should only contain behavior that is truly shared and reusable across many cores and environments.

It should not silently absorb:

- ecosystem conventions
- board workarounds
- one-core quirks
- packaging policy
- deployment policy

If something is specific to one ecosystem, it belongs in `ecosystems/`.

If something is specific to one physical board, it belongs in `boards/`.

If something is specific to one upstream core, it belongs in `cores/<core-name>/`.

### 10. Dependency direction must remain one-way

Folders are not enough by themselves. Dependency direction must also stay disciplined.

The intended direction is:

- framework defines the stable internal contract
- core depends on framework and the selected upstream core
- ecosystem depends on framework and selected core-facing contracts
- board depends on framework, ecosystem selection, and board-specific implementation files
- build/control selects and validates the tuple, then composes the manifests

The reverse should not happen.

In particular:

- boards must not reach into upstream trees directly unless explicitly justified
- ecosystems must not own board constraints or board tool invocation
- cores must not own ecosystem packaging or board pin assignments
- framework must not absorb ecosystem policy or board workarounds

---

## Recommended Repository Structure

    mistable/
    ├── Makefile
    ├── dev
    ├── README.md
    ├── container/
    │   └── Dockerfile
    ├── scripts/
    │   ├── docker.sh
    │   ├── bashrc
    │   ├── sanity.sh
    │   └── test.sh
    ├── doc/
    │   └── ...
    ├── framework/
    │   ├── framework.mk
    │   ├── interfaces/
    │   │   ├── video_if.sv
    │   │   ├── audio_if.sv
    │   │   ├── input_if.sv
    │   │   ├── media_if.sv
    │   │   ├── memory_if.sv
    │   │   └── service_if.sv
    │   ├── rtl/
    │   │   ├── mistable_frame_top.sv
    │   │   ├── reset_clock_if.sv
    │   │   ├── video_pipeline.sv
    │   │   ├── audio_pipeline.sv
    │   │   ├── input_router.sv
    │   │   └── media_router.sv
    │   └── sim/
    ├── cores/
    │   ├── nes/
    │   │   ├── README.md
    │   │   ├── core.mk
    │   │   ├── upstream_sources.mk
    │   │   ├── patches/
    │   │   ├── rtl/
    │   │   │   ├── nes_core_wrap.sv
    │   │   │   ├── nes_input_adapter.sv
    │   │   │   ├── nes_video_adapter.sv
    │   │   │   ├── nes_audio_adapter.sv
    │   │   │   └── nes_media_adapter.sv
    │   │   └── sim/
    │   ├── snes/
    │   │   ├── README.md
    │   │   ├── core.mk
    │   │   ├── upstream_sources.mk
    │   │   ├── rtl/
    │   │   └── sim/
    │   └── core_common/
    │       └── ...
    ├── ecosystems/
    │   ├── sim/
    │   │   ├── README.md
    │   │   ├── ecosystem.mk
    │   │   └── rtl/
    │   ├── mist/
    │   │   ├── README.md
    │   │   ├── ecosystem.mk
    │   │   └── rtl/
    │   ├── mister/
    │   │   ├── README.md
    │   │   ├── ecosystem.mk
    │   │   └── rtl/
    │   ├── mistex/
    │   │   ├── README.md
    │   │   ├── ecosystem.mk
    │   │   └── rtl/
    │   ├── analogue-pocket/
    │   │   ├── README.md
    │   │   ├── ecosystem.mk
    │   │   ├── rtl/
    │   │   └── package/
    │   └── mistable-native/
    │       ├── README.md
    │       ├── ecosystem.mk
    │       └── rtl/
    ├── boards/
    │   ├── sim/
    │   │   └── board.mk
    │   ├── icepi-zero/
    │   │   ├── board.mk
    │   │   ├── build.sh
    │   │   ├── constraints.lpf
    │   │   ├── pll.v
    │   │   └── board_top.sv
    │   ├── mist/
    │   │   ├── board.mk
    │   │   ├── constraints.*
    │   │   ├── pll.v
    │   │   └── board_top.sv
    │   ├── de10-nano/
    │   │   ├── board.mk
    │   │   ├── constraints.*
    │   │   ├── pll.*
    │   │   └── board_top.sv
    │   └── other-board/
    │       ├── board.mk
    │       ├── build.sh
    │       ├── constraints.*
    │       ├── pll.v
    │       └── board_top.sv
    ├── external/
    │   ├── cores/
    │   │   ├── nes_upstream/
    │   │   └── snes_upstream/
    │   └── ip/
    ├── firmware/
    ├── software/
    └── build/

### Structure note

This tree shows the intended long-term shape.

It should not be read as a requirement to fully populate every folder on day one.

The required rule is to preserve the boundaries. Optional directories may remain absent until they are justified by a real implementation.

---

## Layer Responsibilities

### Framework Layer

Location:

    framework/

The framework layer is the stable internal contract that all integrated cores plug into.

This is the portable center of `mistable`.

The framework layer should own things like:

- normalized controller/input interfaces
- video output interfaces
- audio output interfaces
- reset and clock conventions
- ROM/media loading contracts
- memory service interfaces
- service request interfaces

The framework layer should **not** know NES internals, SNES internals, MiST-specific assumptions, MiSTer-specific runtime details, Pocket packaging details, or board pin assignments.

It should also avoid becoming a bucket for future convenience features that are not yet proven to be universal.

#### Example framework files

- `framework/rtl/mistable_frame_top.sv`
- `framework/rtl/video_pipeline.sv`
- `framework/rtl/audio_pipeline.sv`
- `framework/rtl/input_router.sv`
- `framework/rtl/media_router.sv`
- `framework/interfaces/video_if.sv`
- `framework/interfaces/audio_if.sv`
- `framework/interfaces/input_if.sv`
- `framework/interfaces/media_if.sv`

The framework top should represent the stable shape that any selected core plugs into.

---

### Core Layer

Location:

    cores/<core-name>/

Each core directory is the integration layer for one core.

Examples:

- `cores/nes/`
- `cores/snes/`

Each core layer should own:

- wrapper top for that core
- adapter logic between the upstream core and the `mistable` framework contract
- core-specific source manifest
- core-specific documentation
- optional core-specific simulation support

It should **not** own board constraints, board programming scripts, or ecosystem packaging logic.

#### Example NES wrapper responsibilities

- map framework button/input buses to the upstream NES controller interface
- adapt upstream video output format to framework video format
- adapt upstream audio output to framework audio format
- adapt ROM/cartridge/media loading into the form expected by the upstream core

#### Example NES files

    cores/nes/
    ├── README.md
    ├── core.mk
    ├── upstream_sources.mk
    └── rtl/
        ├── nes_core_wrap.sv
        ├── nes_input_adapter.sv
        ├── nes_video_adapter.sv
        ├── nes_audio_adapter.sv
        └── nes_media_adapter.sv

#### Core portability rule

A core wrapper should know:

- what the upstream core expects
- what the `mistable` framework provides

It should **not** directly encode the full behavior of:

- MiST
- MiSTer
- MiSTeX
- Analogue Pocket

That logic belongs in the ecosystem layer.

---

### Ecosystem Layer

Location:

    ecosystems/<ecosystem-name>/

This is the key layer that keeps the repository portable without duplicating cores.

Examples:

- `ecosystems/mist/`
- `ecosystems/mister/`
- `ecosystems/mistex/`
- `ecosystems/analogue-pocket/`
- `ecosystems/sim/`
- `ecosystems/mistable-native/`

An ecosystem adapter owns how the stable `mistable` framework is realized inside a particular external environment.

#### Why this layer exists

MiST, MiSTer, MiSTeX, and Analogue Pocket are not just physical boards.

They differ in things like:

- runtime assumptions
- packaging and deployment model
- menu or host integration expectations
- media and file layout conventions
- common service or framework behaviors

Those differences should be represented explicitly in the repo, not hidden inside core wrappers or board folders.

#### Ecosystem layer should own

- framework-to-ecosystem adaptation
- ecosystem-specific top-level glue
- ecosystem packaging format and metadata generation where needed
- runtime or environment-facing conventions

#### Ecosystem layer should not own

- upstream core internals
- board pin constraints
- board PLLs
- vendor-specific board synthesis, place-and-route, or programming scripts

#### Analogue Pocket note

Analogue Pocket belongs here because it is not merely a board realization. It includes ecosystem-specific packaging and metadata expectations.

#### MiSTer note

MiSTer belongs here because it represents more than a raw FPGA target. It carries ecosystem-level conventions and shared environment expectations.

#### MiSTeX note

MiSTeX belongs here because it is explicitly organized around a ports-and-board-support model rather than being just a single board folder.

#### MiST note

MiST can still be represented as an ecosystem because it has shared conventions and reused common modules, even though historically it is more board-centric than some newer environments.

#### Lean implementation rule

This structure defines the long-term architecture, but the repository should only fully populate ecosystem directories that are actually being proven.

For example, it is reasonable to begin with:

- `ecosystems/sim/`
- one real target ecosystem

and add others only after the boundaries survive a real integration.

---

### Board Layer

Location:

    boards/<board-name>/

Examples:

- `boards/sim/`
- `boards/icepi-zero/`
- `boards/mist/`
- `boards/de10-nano/`

This layer owns how a selected framework+core+ecosystem combination is physically realized on a specific board.

#### Board naming note

Board names should refer to physical realizations.

If a name such as `mist` appears under both `ecosystems/` and `boards/`, the meanings are different:

- `ecosystems/mist/` means MiST-family environment conventions
- `boards/mist/` means the physical MiST board realization

That distinction must stay explicit in docs and build logic.

#### Simulation board

The simulation board should define how the selected design is built and run under simulation.

Example:

    boards/sim/board.mk

#### Physical board

A board directory should contain only board-specific items.

Example:

    boards/icepi-zero/
    ├── board.mk
    ├── build.sh
    ├── constraints.lpf
    ├── pll.v
    └── board_top.sv

A board directory should own:

- synthesis and place-and-route invocation
- board pin constraints
- board PLL wrapper
- board-specific top-level integration
- optional programming convenience wrapper

A board directory should **not** own core internals or ecosystem-level adaptation logic.

---

### Upstream Third-Party Layer

Location:

    external/

This directory holds imported upstream dependencies.

Examples:

- `external/cores/nes_upstream`
- `external/cores/snes_upstream`
- `external/ip/...`

These should be brought in as Git submodules unless there is a strong reason to use subtree instead.

#### Rule

Treat `external/cores/<name>_upstream` as upstream-owned.

That means:

- do not put board glue there
- do not put repo-specific shell scripts there
- do not put local target-specific hacks there unless absolutely necessary
- prefer wrapper and adapter logic in `cores/<name>/`
- prefer ecosystem glue in `ecosystems/<name>/`

#### Why this matters

This keeps the upstream upgrade path clean.

You want to be able to:

- pin to a known-good upstream commit
- update to a newer upstream commit later
- keep your local integration logic separate
- review upstream movement clearly in Git history

---

### Build / Control Layer

Primary files:

- root `Makefile`
- `scripts/*.sh`
- `container/Dockerfile`

This layer is the control surface.

It answers questions like:

- which core is selected
- which ecosystem is selected
- which board is selected
- which build action is requested
- where artifacts go

The build layer should stay explicit.

It should also validate that the requested combination is supported.

#### Example policy

The root build should fail early and clearly if an unsupported combination is requested.

Examples:

- reject unsupported ecosystem/board pairs
- reject missing packaging targets for a specific ecosystem
- reject cores that do not yet implement a required adapter

This keeps the matrix intentional instead of accidental.

---

## Imported Upstream Cores

### Recommended Default: Git Submodule

Preferred path for known-good cores such as NES:

    git submodule add <UPSTREAM_URL> external/cores/nes_upstream
    git commit -m "Add upstream NES core as submodule"

This gives the project:

- pinned upstream commits
- preserved upstream history
- explicit, reviewable updates
- clean separation from local integration logic

#### Clone with submodules

    git clone --recurse-submodules <repo-url>

#### Update a submodule intentionally

    git submodule update --remote external/cores/nes_upstream
    git add external/cores/nes_upstream
    git commit -m "Update upstream NES core"

#### Why submodules are preferred here

Submodules fit the discipline goal well because they make upstream movement explicit.

The project records:

- which upstream repo is used
- which exact commit is pinned
- when the project chooses to advance that pin

#### Practical exception

Default to submodules for clean upstream projects.

Use subtree or vendoring only when the upstream workflow, layout, or expected modification pattern makes submodules impractical.

Even then, keep repo-specific integration outside the imported tree whenever possible.

---

## Alternative: Git Subtree

Subtree may be appropriate when:

- contributors strongly dislike submodule workflow
- the project expects heavier local modification inside the vendored tree
- simpler one-shot clone behavior matters more than clean upstream separation

Even then, the same rule should apply:

- keep repo-specific integration outside the imported tree whenever possible

---

## Wrapper-Based Integration Model

The preferred integration pattern is:

- upstream core remains mostly untouched
- local wrapper adapts upstream core to framework contract
- ecosystem layer adapts framework behavior to a selected ecosystem
- board layer realizes the design on specific hardware

### NES example

Upstream core:

    external/cores/nes_upstream/

Local wrapper and adapters:

    cores/nes/rtl/

Ecosystem-specific adaptation:

    ecosystems/<ecosystem-name>/rtl/

Board-specific realization:

    boards/<board-name>/

The core wrapper is the place that should know both:

- what the upstream NES core expects
- what the `mistable` framework provides

The ecosystem layer is the place that should know both:

- what the selected ecosystem expects
- how the `mistable` framework is presented into that ecosystem

The board layer is the place that should know both:

- what the selected hardware requires
- how to build and wire the design for that hardware

#### Example wrapper top

    module nes_core_wrap (
        input  logic        clk,
        input  logic        rst_n,

        input  logic [15:0] buttons_p1,
        input  logic [15:0] buttons_p2,

        output logic [7:0]  video_r,
        output logic [7:0]  video_g,
        output logic [7:0]  video_b,
        output logic        video_hs,
        output logic        video_vs,
        output logic        video_de,

        output logic signed [15:0] audio_l,
        output logic signed [15:0] audio_r
    );
        // local adapters
        // upstream core instance
    endmodule

The rest of the repo should talk to `nes_core_wrap`, not directly to vendor RTL.

---

## Source Manifest Strategy

Do not allow every ecosystem or board file to duplicate long source lists.

Use a layered manifest model.

### Framework manifest

`framework/framework.mk`

Example:

    FRAMEWORK_SRCS += \
    	framework/interfaces/video_if.sv \
    	framework/interfaces/audio_if.sv \
    	framework/interfaces/input_if.sv \
    	framework/interfaces/media_if.sv \
    	framework/interfaces/memory_if.sv \
    	framework/interfaces/service_if.sv \
    	framework/rtl/mistable_frame_top.sv \
    	framework/rtl/reset_clock_if.sv \
    	framework/rtl/video_pipeline.sv \
    	framework/rtl/audio_pipeline.sv \
    	framework/rtl/input_router.sv \
    	framework/rtl/media_router.sv

### Core manifest

`cores/nes/core.mk`

Example:

    CORE_NAME := nes

    include cores/nes/upstream_sources.mk

    CORE_SRCS += \
    	cores/nes/rtl/nes_core_wrap.sv \
    	cores/nes/rtl/nes_input_adapter.sv \
    	cores/nes/rtl/nes_video_adapter.sv \
    	cores/nes/rtl/nes_audio_adapter.sv \
    	cores/nes/rtl/nes_media_adapter.sv

    CORE_SRCS += $(UPSTREAM_NES_SRCS)

    CORE_DEFINES += CORE_NES

### Ecosystem manifest

`ecosystems/mister/ecosystem.mk`

Example:

    ECOSYSTEM_NAME := mister

    ECOSYSTEM_SRCS += \
    	ecosystems/mister/rtl/mister_env_top.sv \
    	ecosystems/mister/rtl/mister_video_adapter.sv \
    	ecosystems/mister/rtl/mister_audio_adapter.sv \
    	ecosystems/mister/rtl/mister_input_adapter.sv

    ECOSYSTEM_DEFINES += ECOSYSTEM_MISTER

### Board manifest

`boards/icepi-zero/board.mk`

Example:

    BOARD_NAME := icepi-zero

    BOARD_SRCS += \
    	boards/icepi-zero/pll.v \
    	boards/icepi-zero/board_top.sv

    BOARD_CONSTRAINTS := boards/icepi-zero/constraints.lpf

### Upstream source manifest

`cores/nes/upstream_sources.mk`

This file should explicitly list the upstream files actually used by the integration.

Example:

    UPSTREAM_NES_SRCS += \
    	external/cores/nes_upstream/file_a.v \
    	external/cores/nes_upstream/file_b.v \
    	external/cores/nes_upstream/file_c.sv

### Why explicit manifests are preferred

Avoid recursive wildcards and magical file discovery for HDL whenever practical.

Explicit manifests are better because they make it obvious:

- what files are used
- in what order they are presented
- what changed when the integration evolves

---

## Top-Level Makefile Model

The root `Makefile` should stay small and expressive.

Example:

    CORE ?= nes
    ECOSYSTEM ?= sim
    BOARD ?= sim

    include framework/framework.mk
    include cores/$(CORE)/core.mk
    include ecosystems/$(ECOSYSTEM)/ecosystem.mk
    include boards/$(BOARD)/board.mk

This makes selection explicit:

- `CORE=nes`
- `ECOSYSTEM=sim`
- `ECOSYSTEM=mist`
- `ECOSYSTEM=mister`
- `ECOSYSTEM=mistex`
- `ECOSYSTEM=analogue-pocket`
- `BOARD=sim`
- `BOARD=icepi-zero`
- `BOARD=de10-nano`

### Compatibility validation

The root build should also include a compatibility check.

Example approach:

    ifeq ($(ECOSYSTEM),mister)
    ifneq ($(BOARD),de10-nano)
    $(error ECOSYSTEM=mister currently requires BOARD=de10-nano)
    endif
    endif

The exact mechanism can evolve, but the principle should remain:

- supported tuples are explicit
- unsupported tuples fail early
- no false promise of universal combinability

### Example commands

    make sim CORE=nes ECOSYSTEM=sim BOARD=sim
    make bitstream CORE=nes ECOSYSTEM=mist BOARD=mist
    make bitstream CORE=nes ECOSYSTEM=mister BOARD=de10-nano
    make bitstream CORE=nes ECOSYSTEM=mistex BOARD=icepi-zero
    make package CORE=nes ECOSYSTEM=analogue-pocket BOARD=<supported-board>

The exact target names can evolve, but the principle should stay the same.

---

## Simulation Model

A simulation path should still be represented with the same discipline.

This can be done with:

- `ecosystems/sim/`
- `boards/sim/`

This keeps simulation from becoming a special case with a totally separate structure.

### Example pattern

    SIM_DIR := build/vobj
    SIM_BIN := $(SIM_DIR)/sim

    .PHONY: sim

    sim:
    	mkdir -p $(SIM_DIR)
    	verilator -cc \
    		$(FRAMEWORK_SRCS) \
    		$(CORE_SRCS) \
    		$(ECOSYSTEM_SRCS) \
    		$(BOARD_SRCS) \
    		sim/tb.cpp \
    		$(addprefix -D,$(CORE_DEFINES)) \
    		$(addprefix -D,$(ECOSYSTEM_DEFINES)) \
    		--exe \
    		-Mdir $(SIM_DIR) \
    		-o sim
    	$(MAKE) -C $(SIM_DIR) -f V<sim-top>.mk
    	./$(SIM_BIN)

The simulation flow should consume the selected manifests. It should not hardcode NES-specific or one-ecosystem-specific behavior directly.

---

## Board Target Model

A board target should look like the disciplined board folders you admire.

Example:

    boards/icepi-zero/
    ├── board.mk
    ├── build.sh
    ├── constraints.lpf
    ├── pll.v
    └── board_top.sv

### board.mk

Should own:

- synthesis
- place-and-route
- bitstream packaging
- board-specific variable knobs

### build.sh

Should be thin.

It should sequence convenience operations such as:

- clean
- build
- program FPGA
- load firmware if needed

It should not become a second hidden build system.

### board_top.sv

Should be the board-facing top wrapper.

It owns:

- top-level board I/O
- PLL wrapper integration
- connection to the selected ecosystem/framework path

It should not contain deep core logic.

---

## Firmware and Software Separation

If firmware, bootloader, service-side software, or utilities are added later, they should have their own build surface.

Examples:

    firmware/
    software/

These should use their own Makefiles rather than being buried inside board or ecosystem targets.

This preserves a clear split between:

- simulation build
- FPGA bitstream build
- firmware build
- software build
- packaging build

---

## Core Documentation Requirements

Each integrated core should carry its own local README.

Example:

    cores/nes/README.md

That README should document:

- upstream repo URL
- whether imported as submodule or subtree
- pinned upstream commit or tag
- purpose of local wrapper
- local adaptation modules
- known local patches, if any
- how to validate the integration
- how to update upstream

### Example README contents

- Upstream: `<url>`
- Pinned commit: `<hash>`
- Local wrapper top: `cores/nes/rtl/nes_core_wrap.sv`
- Validation command: `make sim CORE=nes ECOSYSTEM=sim BOARD=sim`
- Known local patches: none / listed

---

## Ecosystem Documentation Requirements

Each ecosystem adapter should carry its own local README.

Example:

    ecosystems/analogue-pocket/README.md

That README should document:

- what this ecosystem means in `mistable`
- expected packaging or deployment model
- top-level adapter modules
- special metadata or packaging outputs
- validation path
- which boards, if any, are currently supported for that ecosystem

This becomes especially important for:

- MiSTer
- MiSTeX
- Analogue Pocket

because they carry more than raw board-level meaning.

---

## Upstream Update Workflow

The project should keep upstream updates deliberate.

Recommended flow:

1. Update submodule to a newer upstream commit.
2. Run baseline environment checks.
3. Run core-specific simulation/build.
4. Prefer wrapper-only adjustments if adaptation changes are needed.
5. Prefer ecosystem-layer changes before patching upstream.
6. Avoid patching upstream unless wrapper-based integration is insufficient.
7. Commit upstream movement separately from local integration changes when possible.

### Example

    git submodule update --remote external/cores/nes_upstream
    git add external/cores/nes_upstream
    git commit -m "Update upstream NES core"

    make shell
    make sanity
    make sim CORE=nes ECOSYSTEM=sim BOARD=sim

If local integration must change, prefer a separate commit.

This keeps history clear:

- one commit says upstream moved
- another commit says local wrapper adapted
- another commit says ecosystem adapter changed, if needed

---

## Local Patch Policy

Patching upstream should be the exception, not the default.

If a local patch inside the upstream tree is unavoidable:

- keep the patch minimal
- document it in `cores/<core>/README.md`
- explain why wrapper-only integration was insufficient
- explain why ecosystem-layer adaptation was insufficient
- note whether the patch should be proposed upstream later

A small `PATCHES.md` may also be useful.

---

## Naming and Boundary Rules

Use simple naming conventions.

### Framework files

- `mistable_frame_top.sv`
- `video_if.sv`
- `audio_if.sv`
- `input_if.sv`
- `media_if.sv`
- `memory_if.sv`
- `service_if.sv`
- `video_pipeline.sv`
- `audio_pipeline.sv`
- `input_router.sv`
- `media_router.sv`

### Core files

- `<core>_core_wrap.sv`
- `<core>_input_adapter.sv`
- `<core>_video_adapter.sv`
- `<core>_audio_adapter.sv`
- `<core>_media_adapter.sv`

### Ecosystem files

- `<ecosystem>_env_top.sv`
- `<ecosystem>_video_adapter.sv`
- `<ecosystem>_audio_adapter.sv`
- `<ecosystem>_input_adapter.sv`
- `<ecosystem>_package.mk`
- `ecosystem.mk`

### Board files

- `board_top.sv`
- `pll.v`
- `constraints.*`
- `board.mk`
- `build.sh`

### Rule of thumb

If a file name feels too clever, it probably is.

Keep names boring and obvious.

---

## Change-Control Rule for This Document

This document is frozen as the architectural repository-structure baseline.

It should not be casually edited for wording preference, speculative future ideas, or opportunistic cleanup.

It should only be revised when one or more of the following occurs:

- a real integration exposes a boundary flaw
- a naming collision creates persistent confusion
- the build/control ownership split proves unworkable in practice
- the upstream import/update workflow requires a structural exception
- a proven ecosystem or board path cannot be represented cleanly within these rules

When revised, changes should be deliberate and reviewable, and should preserve the original goal of maintainability, portability, explicitness, and bounded structure.

---

## First Milestone for Adding NES

Do not try to build a fully feature-complete NES integration first.

The first milestone should be structural.

Definition of done:

- `external/cores/nes_upstream` exists as a submodule
- `cores/nes/rtl/nes_core_wrap.sv` exists
- `cores/nes/core.mk` exists
- `cores/nes/upstream_sources.mk` exists
- `ecosystems/sim/ecosystem.mk` exists
- `boards/sim/board.mk` exists
- root `Makefile` can select `CORE=nes`
- root `Makefile` can select `ECOSYSTEM=sim`
- root `Makefile` can select `BOARD=sim`
- compatibility validation exists for unsupported tuples
- simulation can build with the selected NES wrapper path
- ROM/media path may be stubbed initially if needed

This proves that the structure is sound before complexity grows.

---

## Recommended Development Flow

When working on a specific core integration:

    git checkout main
    git pull --rebase
    git checkout -b core/nes-integration-step1

    make shell
    make sanity
    make sim CORE=nes ECOSYSTEM=sim BOARD=sim

Then make one small, bounded change at a time.

When working on ecosystem adaptation:

    git checkout -b ecosystem/mister-bridge-step1
    make sim CORE=nes ECOSYSTEM=sim BOARD=sim

Then bring in the next ecosystem layer deliberately.

This keeps the repo aligned with the trusted development baseline already established.

---

## Future Compatibility with FuseSoC

This structure is intentionally compatible with introducing FuseSoC later.

Why:

- cores are already separated
- ecosystems are already separated
- boards are already separated
- source manifests are already explicit
- framework/core/ecosystem/board boundaries are already clear

That means future FuseSoC adoption becomes an act of formalizing clean structure, not rescuing a messy one.

Possible future mapping:

- upstream imported core becomes a dependency
- local wrapper becomes your own reusable core entry
- ecosystem adapters become environment-specific targets or generators
- board flows become board targets

Do not add FuseSoC until the structural boundaries feel stable.

---

## Summary

This structure is designed to let `mistable` grow cleanly while staying portable and aligned with the direction of the broader retro-FPGA ecosystem.

It does that by enforcing:

- explicit build surfaces
- stable framework/core/ecosystem/board boundaries
- clean upstream core import paths
- wrapper-based integration
- clear update workflows
- minimal build magic
- portability without per-core ecosystem forks
- explicit validation of supported compatibility tuples

The most important discipline rule is this:

**Keep upstream code intact, keep core integration thin, keep ecosystem behavior in ecosystem folders, keep board-specific glue in board-specific folders, make supported combinations explicit, and keep dependency direction one-way.**

If that rule is maintained, the project can scale across MiST, MiSTer, MiSTeX, Analogue Pocket, and future `mistable`-native environments without losing clarity.
