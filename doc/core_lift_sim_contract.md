# Core Lift to Simulation Contract
#
# Status:
# Frozen working contract for lifting upstream cores into `mistable`
# simulation form without violating the repository structure policy in:
# `doc/multi_core_structure.md`
#
# Purpose:
# This contract defines the repeatable instructions and required outputs
# for taking an upstream FPGA core repository, identifying the real core,
# separating it from platform-specific glue, and integrating it into
# `mistable` as a simulation-first target using:
#
#   CORE=<core_name>
#   ECOSYSTEM=sim
#   BOARD=sim
#
# This contract is intentionally strict.
# It exists to prevent one-off ports, hidden assumptions, wrapper sprawl,
# fake portability, and accidental leakage of board/ecosystem policy into
# the core boundary.
#
# This contract governs only the `CORE=<core_name> ECOSYSTEM=sim BOARD=sim`
# lift path unless additional tuples are explicitly declared and implemented.
#
# This file is both:
# - a human review checklist
# - a strict execution contract for future ChatGPT-assisted core lifts
#
# This contract does not replace `doc/multi_core_structure.md`.
# It operationalizes that frozen repository structure policy for
# repeatable simulation-first core lifting.
#
# This file defines a strict lift-review workflow and deliverable set for
# simulation-first integrations. It does not add new architectural layers,
# does not transfer ownership away from root build/control, and does not
# convert workflow artifacts into mandatory repository-wide structure beyond
# the architectural boundary rules already frozen in
# `doc/multi_core_structure.md`.
#
# Preferred review artifacts named in this file are exactly that:
# preferred lift-review artifacts.
# They are not, by themselves, mandatory permanent repository structure.
# They should be created only when they materially improve reviewability,
# repeatability, provenance, or boundary clarity for the specific lift.
# When omitted, the lift must say so explicitly and explain why.
#
# Nothing in this contract, by itself, promotes a preferred lift-review
# artifact, naming pattern, or per-core helper file into frozen repository
# architecture. Any such promotion requires a separate explicit architectural
# decision that updates `doc/multi_core_structure.md`.
#
# Any conflict between this file and `doc/multi_core_structure.md` must be
# resolved in favor of `doc/multi_core_structure.md`.

# ----------------------------------------------------------------------
# 1. Invocation Template
# ----------------------------------------------------------------------

Use the following recommended instruction pattern when asking ChatGPT to lift a core:

Using `doc/multi_core_structure.md` as the frozen repository contract and
`doc/core_lift_sim_contract.md` as the frozen lift contract, read this
upstream core repo and lift it into a simulation-first `mistable` integration.

Upstream core repo:
<PASTE URL HERE>

Target tuple:
CORE=<core_name>
ECOSYSTEM=sim
BOARD=sim

Required behavior:
1. Read the upstream repo structure first.
2. Identify the real functional core top, not just the board/project wrapper.
3. Audit FPGA primitives, vendor IP, generated cores, board glue, platform glue,
   and memory/clock/reset assumptions before writing integration files.
4. Keep upstream code intact under:
   external/cores/<core_name>_upstream/
5. Put all local integration under:
   cores/<core_name>/
6. Put reusable simulation ecosystem files under:
   ecosystems/sim/
7. Put simulation board realization files under:
   boards/sim/
8. Use explicit source manifests only. No uncontrolled recursive wildcard source gathering.
9. Output:
   - integration summary
   - upstream repo analysis
   - chosen core top and rejected alternatives
   - primitive/vendor/generated-IP audit
   - clock/reset/domain audit
   - memory interface audit
   - retained module boundary inventory
   - excluded wrapper/platform glue audit
   - excluded source summary with exact reasons for exclusion
   - asset/preload/runtime-data contract
   - simulation observability contract
   - legal tuple statement
   - acceptance criteria
   - final directory tree
   - full contents of every new local file
   - full contents of every locally modified non-upstream file
   - patches for any unavoidable upstream modifications
   - exact build command
   - exact sim/run command
   - known gaps, stubs, and assumptions
10. Do not redesign repository architecture.
11. Follow the frozen repository structure exactly.
12. Prefer minimal working simulation first:
   - reset release
   - clocking
   - input path
   - video output
   - audio output if practical
   - ROM/media load path
13. Do not blindly carry vendor primitives, PHYs, board wrappers, or platform policies into the core lift.
14. If required upstream submodules, generated sources, or external assets are missing,
    explicitly stop and report the missing boundary rather than inferring hidden structure.

Core-specific sim files stay under `cores/<core_name>/sim/`.
Core-specific retained upstream source selection stays in
`cores/<core_name>/upstream_sources.mk`, not in ecosystem or board manifests.
Reusable shared sim environment files stay under `ecosystems/sim/` and
`boards/sim/`.
The root build/control layer remains the only authority that validates the
requested tuple and composes framework/core/ecosystem/board manifests.

# ----------------------------------------------------------------------
# 2. Structural Intent
# ----------------------------------------------------------------------

A valid lift must respect the repository structure policy:

- framework stays narrow and boring
- framework remains the primary stable internal contract
- core owns upstream adaptation
- ecosystem owns reusable ecosystem-specific simulation behavior only
- board owns board realization only
- build/control composes explicit manifests and validates legal tuples
- upstream code remains intact whenever possible
- portability comes from changing adapters, not cloning cores
- tuple legality is explicit, not assumed
- dependency direction remains one-way
- do not modify upstream files in place unless the response explicitly documents
  the reason, the exact patch, and why a local wrapper or adapter was insufficient

This contract does not replace `doc/multi_core_structure.md`.
It operationalizes it for repeatable simulation-first core lifting.

Nothing in this file should be interpreted as:
- moving tuple-validation ownership away from root build/control
- redefining the stable `mistable` framework contract
- requiring every named review artifact to exist for every core
- creating a second hidden framework under simulation-specific naming
- promoting a preferred core-side helper file into repository-wide structure
  merely because it appears in an example tree or preferred artifact list

# ----------------------------------------------------------------------
# 3. Required Work Sequence
# ----------------------------------------------------------------------

Every core lift must follow this sequence in order:

Step 1. Read the upstream repository
- inspect repository structure
- identify likely top-level modules
- identify build files, platform wrappers, memory wrappers, clock wrappers,
  ROM loaders, OSD/input layers, and generated IP directories
- identify whether the repo is a pure core repo, a platform repo, or a mixed repo

Step 2. Choose the narrowest valid top
- prefer the narrowest real gameplay/system core top
- do not default to the first visible board/project top
- if multiple candidate tops exist, explain each one and choose the narrowest
  top that still exposes a sensible logical core boundary

Step 3. Perform required audits before integration
- primitive/vendor/generated-IP audit
- clock/reset/domain audit
- memory contract audit
- retained module boundary inventory
- wrapper/platform policy audit
- asset/preload/runtime-data audit
- simulation observability contract
- legal tuple statement
- acceptance criteria

Step 4. Decide what stays and what does not
- retain portable upstream RTL
- exclude platform wrappers
- exclude board wrappers
- exclude vendor-primitive-heavy wrappers when a lower top exists
- replace necessary technology-specific pieces with local wrappers or sim models
- document every exclusion and replacement
- do not copy upstream RTL into local core directories except for documented
  patch artifacts or generated replacement wrappers

Step 5. Build the local integration layer
- core wrapper
- input adapter
- video adapter
- audio adapter
- media/asset adapter
- technology replacement wrappers if needed
- simulation primitive models if needed
- do not edit retained upstream RTL merely to make simulation easier; use local
  wrappers, adapters, techmaps, sim models, or documented patches

Step 6. Hook into ecosystem and board
- `ecosystems/sim/`
- `boards/sim/`
- explicit Makefile composition
- explicit tuple legality through the root build/control path

Step 7. Define acceptance checks
- simulation must have concrete pass/fail intent, not just “compiles”

Step 8. Emit full deliverable
- final tree
- every new local file in full
- every modified local non-upstream file in full
- exact build/run command
- clear limitations

# ----------------------------------------------------------------------
# 4. Preferred Lift Review Artifacts
# ----------------------------------------------------------------------

The artifacts below are preferred review outputs for a disciplined,
simulation-first lift performed under this contract.

They are strongly recommended because they make the lift reviewable, repeatable,
and explicit. They are not permanent architectural requirements by themselves.
They should not be interpreted as new mandatory repository-wide structure beyond
the boundary rules already frozen in `doc/multi_core_structure.md`.

When a given artifact is unnecessary for a particular core, the response must
state that explicitly and explain why the omission is correct.

If a lift review emits one of these artifacts, it may persist it under the
core directory shown below when doing so materially improves repeatability,
maintainability, or provenance for that lift. If a given artifact is not needed
for that core, the lift review must say so explicitly rather than creating empty
ceremony files.

## 4.1 Primitive / Vendor / Generated-IP Audit

Preferred review artifact:
`cores/<core_name>/primitive_audit.md`

Before writing integration files, scan the upstream repo for:
- FPGA primitives
- vendor IP wrappers
- generated cores
- hard-macro wrappers
- synthesis-only library cells
- board-specific technology glue

For each identified item, record:
- primitive/module name
- vendor/family
- file path
- purpose
- architectural location:
  - real core logic
  - board wrapper
  - platform wrapper
  - clocking
  - memory PHY
  - I/O cell layer
  - video serialization
  - startup/config/JTAG
  - optimization-only implementation
- required action:
  - exclude behind boundary
  - replace with local generic wrapper
  - provide behavioral simulation model
  - temporarily stub with explicit limitation
- justification

Never treat vendor primitives as ordinary source files.
Do not hide them inside wildcard manifests either.

Examples to search for include, but are not limited to:
- Xilinx: MMCME2, PLLE2, BUFG, BUFIO, BUFR, IDDR, ODDR, IOBUF,
  RAMB18, RAMB36, DSP48, STARTUPE2, BSCANE2
- Intel/Altera: altpll, altsyncram, dcfifo, cyclonev_*, fiftyfivenm_*
- Lattice: SB_PLL40, SB_RAM40_4K, EHXPLLL, DP16KD, TRELLIS_*
- Gowin: rPLL, PLLVR, DPB, IOBUF
- Generic generated wrappers: clk_wiz, fifo_generator, mig, emif, sdram_phy,
  ddr_phy, serdes, hyperram_phy

Preferred handling order:
a. remove platform-only primitive usage by choosing a lower top
b. replace with a mistable-local wrapper
c. provide a behavioral sim model
d. stub only if unavoidable, and document clearly

Preferred local locations for replacements:
- `cores/<core_name>/rtl/techmap/` for retained, synthesis-neutral
  replacement or isolation wrappers
- `cores/<core_name>/sim/prims/` for simulation-only behavioral primitive
  models

Rule:
If the upstream design depends on encrypted, black-box, or tool-generated IP
that cannot be meaningfully simulated in an open flow, the lift must explicitly
stop at that boundary and declare the sim incomplete rather than fake behavior.

Behavioral primitive models must preserve only the minimum semantics required for
repeatable simulation and must not imply synthesis portability.

Generated non-vendor assets or generated support sources required by the core are
part of the retained source contract and must be either reproduced explicitly or
declared missing.

## 4.2 Clock / Reset / Domain Audit

Preferred review artifact:
`cores/<core_name>/clock_reset_audit.md`

Required analysis:
- all clock inputs
- all internally generated clocks
- all clock-enable-derived timing domains
- reset polarity
- reset source
- reset sequencing
- async vs sync reset behavior
- cross-domain paths that matter for first-pass sim
- whether the candidate top includes board-level PLL/MMCM/DCM/clock routing logic
- whether the real core can be lifted below that layer
- default startup values for key stateful interfaces if known

For each domain, record:
- domain name
- nominal purpose
- upstream source
- whether retained, replaced, or collapsed for sim
- reset behavior
- risk if simplified

Rules:
- board-level clock generation should stay out of the core lift when possible
- do not silently merge distinct domains unless explicitly documented
- if sim uses simplified clocking, state exactly how and why
- startup sequencing must explicitly define the ordering relationship between:
  - clock start
  - asset preload
  - reset assertion
  - reset release
  - first frame eligibility

## 4.3 Memory Contract Audit

Preferred review artifact:
`cores/<core_name>/memory_contract.md`

This is expected even if no obvious vendor primitive exists.

Identify:
- program ROM path
- character/tile/sprite ROM path
- cartridge/media path
- save RAM path
- framebuffer path
- work RAM / CPU RAM path
- DMA/fetch/arbitration paths
- cache/fill assumptions if present
- SDRAM/DDR/PSRAM/HyperRAM assumptions
- latency assumptions
- burst behavior
- preload behavior
- byte/word endianness concerns
- any mapper or bank-switching logic relevant to media load
- arbitration ownership and priority assumptions

The goal is to find the first logical memory boundary above board/PHY glue.

Rules:
- do not stop analysis at the primitive layer
- do not drag PHY assumptions into the lifted core if a higher logical memory interface exists
- if memory timing is simplified in sim, document what behavior is preserved and what is not

## 4.4 Wrapper / Platform Policy Audit

Preferred review artifact:
`cores/<core_name>/wrapper_audit.md`

Not all bad wrappers contain primitives.
Some wrappers encode policy.

Identify and classify wrappers that contain:
- OSD/menu systems
- user I/O register conventions
- MiST/MiSTer/MiSTeX/Analogue Pocket-specific control/status buses
- scan doubler policy
- video timing policy
- board reset/power-up policy
- on-screen loader behavior
- platform-specific ROM loading
- peripheral routing
- packaging/deployment logic

For each wrapper, record:
- file path
- role
- whether it is:
  - real core logic
  - platform policy
  - board realization
  - ecosystem adaptation
  - generated glue
- action:
  - retain
  - exclude
  - replace with local adapter
- reason

Rule:
A plain RTL wrapper can still be the wrong architectural boundary.

## 4.5 Asset / Preload / Runtime Data Contract

Preferred review artifact:
`cores/<core_name>/asset_contract.md`

Document exactly:
- required ROM/BIOS/media files
- expected filenames
- expected binary format
- whether headers must be stripped
- endian handling
- mapper/config side data if needed
- location under the repo for first-pass sim
- how preload is performed
- when preload occurs relative to reset release
- save-data expectations if any
- what must be stubbed if real assets are unavailable
- whether the asset can be stored in-repo for test purposes or must be user-supplied
- distinguish between redistributable in-repo smoke-test assets and
  user-supplied proprietary assets
- checksum or smoke-test asset recommendation if a freely redistributable test asset is unavailable
- distinguish power-on initialized assets from runtime-injected assets

Rule:
Simulation must be repeatable.
Runtime assets are part of the contract, not an afterthought.

## 4.6 Legal Tuple Statement

Preferred review artifact when useful:
- inline in the lift report, or
- `cores/<core_name>/README.md`, or
- another existing explicit, reviewable mechanism already supported by the root build

This lift may state which tuples are currently supported, but it must not
assume ownership of tuple validation, cross-layer policy, or build control.

Root build/control remains responsible for final tuple validation, early failure
for unsupported combinations, and composition of framework/core/ecosystem/board
manifests.

At minimum, state whether:
- `CORE=<core_name> ECOSYSTEM=sim BOARD=sim`
is valid now.

If additional tuples are not yet supported, do not imply they exist.

Example statement pattern:

Supported now:
- `<core_name>:sim:sim`

Rule:
Portability must be earned.
Do not create fake matrix claims.
Do not move tuple-validation ownership out of root build/control.

If the root build already has another explicit, reviewable tuple-legality
mechanism, use that instead and document it clearly.

A per-core file such as `supported_tuples.mk` may be used only if:
- the existing root build/control path explicitly supports consuming it
- doing so does not shift validation ownership away from the root build
- the response documents that it is a local declaration input, not the
  validation authority

## 4.7 Acceptance Criteria

Preferred review artifact:
`cores/<core_name>/acceptance.md`

Define first-pass success criteria such as:
- build completes
- simulation resets cleanly
- video sync becomes active
- frame activity is observed
- non-blank active video area is observed when expected
- video output demonstrates non-constant pixel behavior beyond reset/blanking
- at least one visible state change occurs
- controller input changes internal behavior or output
- audio activity is non-zero if audio is expected
- media preload path executes if required

Also define:
- what is not yet validated
- what is stubbed
- what known simplifications exist

All gaps must be classified as:
- temporary stub
- deferred architectural adapter
- unsupported feature
- unknown upstream dependency

If video, media, or reset behavior cannot be observed without guessing through a
missing or opaque upstream boundary, acceptance must fail explicitly.

Rule:
“Compiles” is not acceptance.

Driving an input signal without any resulting internal or output state change is
not a valid input-success claim.

## 4.8 Upstream Provenance

Preferred review artifact:
`cores/<core_name>/UPSTREAM.md`

Record:
- upstream repo URL
- branch/tag/commit if known
- subdirectory imported if applicable
- selected upstream top
- excluded files and why
- replacement files and why
- any assumptions made due to incomplete upstream metadata

Rule:
Future updates must be reviewable, not archaeological.

Do not remove or rewrite upstream license files, headers, or attribution notices.
Any copied patch artifacts must preserve original copyright and license context
where applicable.

## 4.9 Retained Module Boundary Inventory

Preferred review artifact:
`cores/<core_name>/module_boundary_inventory.md`

Document:
- major retained modules
- file path
- role in system
- whether:
  - core logic
  - timing/video pipeline
  - audio pipeline
  - CPU subsystem
  - memory subsystem
  - mapper/media subsystem
  - wrapper/adapter
- why retained
- whether directly instantiated by the chosen top or indirectly required

Rule:
The retained module set must be explainable as a coherent logical core, not a pile of files that happened to compile.

## 4.10 Simulation Observability Contract

Preferred review artifact:
`cores/<core_name>/sim_observability.md`

Document:
- signals or events used to determine reset completion
- signals or events used to determine video activity
- signals or events used to determine frame cadence
- signals or events used to determine non-blank active video output
- signals or events used to determine audio activity
- signals or events used to determine media load success
- signals or events used to determine input responsiveness
- whether pass/fail is visual, signal-based, log-based, or checksum-based

Rule:
Acceptance checks must be observable in a repeatable way, not dependent on manual interpretation alone.

## 4.11 Upstream Patch Policy

Default rule:
- upstream files must remain unmodified under
  `external/cores/<core_name>_upstream/`

If a patch is unavoidable:
- prefer a local wrapper or adapter first
- otherwise place patches under:
  `cores/<core_name>/patches/`
- document:
  - patched upstream file path
  - reason patch was required
  - why a local wrapper was insufficient
  - whether the patch is expected to be upstreamable

If the patch is tiny and emitted inline in a response, it must still be mirrored as
a persistent local patch artifact in the repository layout.

Rule:
A lift must make the upstream/local modification boundary obvious.

## 4.12 Upstream Submodule / External Dependency Policy

You must explicitly identify required upstream submodules, fetched artifacts,
generated source steps, or external helper repositories when present.

Document:
- path or reference
- purpose
- whether required for build, sim, asset generation, or packaging
- whether present or missing
- whether the lift can proceed without it

Rules:
- do not silently flatten or re-author missing upstream submodules
- do not infer hidden structure from partial imports
- if a required dependency is absent, stop at that boundary and report it clearly

# ----------------------------------------------------------------------
# 5. Directory Layout Rules
# ----------------------------------------------------------------------

A first-pass simulation lift must preserve repository boundaries in a form
substantially equivalent to the structure below.

This tree is a preferred layout for reviewable, disciplined simulation-first
integration. It should not be interpreted as requiring every listed file or
subdirectory to exist for every core on day one.

The non-negotiable requirement is to preserve the architectural boundary lines:
- upstream code stays under `external/cores/`
- local core integration stays under `cores/<core_name>/`
- reusable simulation ecosystem files stay under `ecosystems/sim/`
- simulation board realization files stay under `boards/sim/`
- root build/control remains the composition and validation authority

mistable/
├── Makefile
├── framework/
│   └── ...
├── ecosystems/
│   └── sim/
│       ├── ecosystem.mk
│       └── rtl/
│           └── ...
├── boards/
│   └── sim/
│       ├── board.mk
│       └── ...
├── external/
│   └── cores/
│       └── <core_name>_upstream/
└── cores/
    └── <core_name>/
        ├── README.md
        ├── UPSTREAM.md
        ├── core.mk
        ├── upstream_sources.mk
        ├── patches/
        │   └── ...
        ├── rtl/
        │   ├── <core_name>_core_wrap.sv
        │   ├── <core_name>_input_adapter.sv
        │   ├── <core_name>_video_adapter.sv
        │   ├── <core_name>_audio_adapter.sv
        │   ├── <core_name>_media_adapter.sv
        │   └── techmap/
        │       └── ...
        └── sim/
            ├── roms/
            ├── prims/
            │   └── ...
            └── ...

Possible additional preferred lift-review artifacts, when justified:
- `primitive_audit.md`
- `clock_reset_audit.md`
- `memory_contract.md`
- `wrapper_audit.md`
- `asset_contract.md`
- `acceptance.md`
- `module_boundary_inventory.md`
- `sim_observability.md`

Rules:
- upstream code stays under `external/cores/`
- local integration stays under `cores/<core_name>/`
- ecosystem simulation files stay under `ecosystems/sim/`
- board simulation realization files stay under `boards/sim/`
- `boards/sim/` represents the repository's shared simulation realization for
  the `BOARD=sim` tuple. It is a simulation-only board slot used by the root
  build/control path, not a general license to redefine board naming or to move
  physical board policy into simulation.
- `ecosystems/sim/` and `boards/sim/` must remain generic/shared unless a file
  is explicitly justified as reusable simulation infrastructure; core-specific
  logic belongs under `cores/<core_name>/`
- do not place ecosystem logic into the core wrapper
- do not place board realization into the ecosystem
- do not place platform-specific policy into framework
- do not copy retained upstream RTL into `cores/<core_name>/rtl/` merely for convenience;
  retain it under `external/cores/<core_name>_upstream/` and wrap it locally

# ----------------------------------------------------------------------
# 6. Preferred Core-Side Lift Artifacts
# ----------------------------------------------------------------------

The items in this section are preferred per-core lift artifacts for a
disciplined, reviewable simulation-first integration.

They are not intended to redefine the frozen repository architecture or to
transfer composition/validation ownership away from the root build/control
layer. The actual mandatory architectural boundaries remain governed by
`doc/multi_core_structure.md`.

When a specific artifact is unnecessary for a given core, that omission must be
stated explicitly and justified.

These artifacts should be created only when they materially improve clarity,
reviewability, or repeatability for the specific lift. They are preferred lift
outputs, not a blanket requirement that every core permanently carry every file.

## 6.1 README.md
Should summarize:
- upstream source
- chosen top
- tuple
- simulation scope
- major limitations
- asset expectations
- input mapping
- video/audio notes

## 6.2 upstream_sources.mk
Should contain an explicit retained upstream source manifest.
No uncontrolled wildcard crawling.

Wildcard use is allowed only for tightly scoped local generated lists if the
deliverable explicitly shows the exact matched set.

Wildcard use must never be used to discover upstream source membership.

It must not blindly include:
- board wrappers
- excluded platform wrappers
- generated vendor IP being replaced
- primitive libraries being handled elsewhere

Source manifests should be grouped by functional role when practical
(e.g. core logic, video path, audio path, CPU/memory path, adapters).

This manifest may reference retained upstream files located under
`external/cores/<core_name>_upstream/`, but only those explicitly selected
for the retained module boundary.

Every retained upstream file referenced in `upstream_sources.mk` must be
explainable by the retained module boundary inventory.

## 6.3 core.mk
Should include:
- `upstream_sources.mk`
- local wrapper/adapters
- local techmap wrappers if needed
- local simulation primitive models from `sim/prims/` if used by the sim build

Tuple validation must remain at the root build/control layer.
A core-side file may declare support information only if the existing root build
already has an explicit way to consume it without surrendering validation ownership.

## 6.4 <core_name>_core_wrap.sv
This is the stable local integration point.
It adapts the retained upstream core to the stable `mistable` framework contract.

It must not become:
- a dumping ground for ecosystem policy
- a board top
- a reimplementation of upstream logic
- a mixed MiST/MiSTer/Pocket wrapper
- the place where tuple legality, ecosystem ownership, board realization, or
  simulation policy is implicitly redefined

## 6.5 input/video/audio/media adapters
These should normalize the chosen core to the stable framework-facing contract.

## 6.6 techmap wrappers
Use only where genuinely needed.
These exist to replace or isolate technology-specific constructs.

## 6.7 simulation primitive models
Only use if a primitive cannot be eliminated at a cleaner boundary.

Rule:
Local integration files should follow the `<core_name>_*` naming convention unless
there is a documented reason not to.

# ----------------------------------------------------------------------
# 7. Preferred Simulation Convenience Interface
# ----------------------------------------------------------------------

The lifted core must adapt the upstream design to the stable `mistable`
framework contract first.

That framework contract remains primary.
Any simulation-facing normalization exists only as a subordinate convenience
layer for simulation and observability. It does not replace, redefine, or
supersede the stable framework contract.

For simulation-first lifts, any additional sim-facing compatibility shims should
live in `ecosystems/sim/` and/or `boards/sim/` when they are reusable, not as
a hidden second framework and not as a new architecture owned by the core lift.

The core wrapper may include only the minimum core-local adaptation needed to:
- connect the retained upstream design to the stable framework contract
- expose the retained logical core boundary clearly
- avoid pushing ecosystem policy or board realization back into the core layer

A first-pass local sim adapter may expose a convenience interface for
testbench use, while the stable `mistable` framework contract remains
authoritative.

That convenience interface exists only to support simulation bring-up,
observability, and repeatable testbench interaction. It is not a second
framework, not a replacement for the stable `mistable` framework contract,
and not a new architectural boundary.

If the current simulation path benefits from a boring normalized interface for
testbench convenience, that interface must be treated as a local simulation
compatibility surface only and documented as such.

A lift must not target this local simulation convenience interface in place of
the stable framework-facing adaptation when a framework-facing adaptation is
feasible.

No file, manifest, wrapper, or testbench may treat this convenience interface
as the primary architectural contract of `mistable`, and no future non-sim
integration may depend on its existence unless a separate architectural change
explicitly promotes it into the frozen repository policy.

This local simulation convenience interface is not the architectural contract of
`mistable`, is not a replacement for the framework contract, and must not be
used to redefine layer ownership, tuple policy, or portability claims.

When such a convenience interface is useful for first-pass sim bring-up, a
common example shape is:

Inputs:
- clk
- rst_n
- buttons_p1[15:0]
- buttons_p2[15:0]
- media_valid
- media_data[7:0]

Outputs:
- media_ready
- video_r[7:0]
- video_g[7:0]
- video_b[7:0]
- video_hs
- video_vs
- video_de
- audio_l[15:0] signed
- audio_r[15:0] signed

If the actual core requires different widths or semantics, adapt locally and
document it.

Rules:
- the stable `mistable` framework contract remains primary
- any sim convenience interface is optional and subordinate
- normalization for simulation convenience must not become a hidden second
  framework
- ecosystem-specific behavior belongs in `ecosystems/<ecosystem>/`
- board realization belongs in `boards/<board>/`
- the core wrapper must not become a dumping ground for simulation, ecosystem,
  and board policy mixed together

# ----------------------------------------------------------------------
# 8. Root Build / Makefile Rules
# ----------------------------------------------------------------------

The root build must remain explicit.

Required properties:
- selects CORE, ECOSYSTEM, BOARD
- composes manifests from:
  - framework
  - core
  - ecosystem
  - board
- validates legal tuples
- exposes an explicit `sim` target
- does not hide source selection behind magical scripts
- treats shell scripts only as convenience wrappers

The primary user-facing simulation command must remain structurally similar to:

make sim CORE=<core_name> ECOSYSTEM=sim BOARD=sim

Rule:
Makefiles own the control plane.

Nothing in this contract transfers validation or composition authority away from
the root build/control layer.

# ----------------------------------------------------------------------
# 9. Non-Negotiable Guardrails
# ----------------------------------------------------------------------

1. Never treat vendor primitives as ordinary source files.
2. Prefer lifting below board/platform wrappers whenever possible.
3. A plain RTL wrapper can still be the wrong architectural boundary.
4. Do not claim portability you have not implemented.
5. Do not duplicate cores by ecosystem name.
6. Do not let framework absorb ecosystem or board policy.
7. Do not let boards reach into upstream trees casually.
8. Do not let ecosystem logic leak into the core wrapper.
9. Do not let a simulation convenience interface become a hidden replacement
   for the stable framework contract.
10. Do not silently simplify clocks, resets, or memory behavior.
11. Do not define success as mere compilation.
12. Do not leave asset handling implicit.
13. Do not lose upstream provenance.
14. Do not use recursive source discovery as a substitute for architecture.
15. `BOARD=sim` refers only to the repository's explicit simulation-board slot
    used by the root build/control composition path. It must not be used to
    smuggle in physical connector mappings, board clocks, board SDRAM topology,
    or board-specific peripheral policy.
16. The testbench may observe the lifted core and drive normalized inputs, but
    it must not re-encode platform policy that properly belongs in local adapters.
17. If a credible first-pass sim cannot be produced without architectural guessing,
    the lift must fail explicitly with a boundary report rather than fabricate integration.
18. Do not remove or rewrite upstream license files, headers, or attribution notices.
19. Do not reinterpret preferred lift-review artifacts as mandatory permanent
    repository structure unless a separate architectural decision explicitly
    promotes them into the frozen repository policy.

# ----------------------------------------------------------------------
# 10. Required Output Format from ChatGPT
# ----------------------------------------------------------------------

When given an upstream core under this contract, ChatGPT must return:

1. Integration summary
2. Upstream repository analysis
3. Chosen core top, rejected alternatives, and the exact reason each rejected top was not the correct architectural boundary
4. Primitive/vendor/generated-IP audit
5. Clock/reset/domain audit
6. Memory contract audit
7. Retained module boundary inventory
8. Wrapper/platform-policy audit
9. Asset/preload/runtime-data contract
10. Simulation observability contract
11. Legal tuple statement
12. Acceptance criteria
13. Final directory tree
14. Full contents of every new local file
15. Full contents of every locally modified non-upstream file
16. Patches for any unavoidable upstream modifications
17. Exact Makefile, manifest, or tuple-declaration additions/changes
18. Exact retained upstream file list referenced by `upstream_sources.mk`
19. Exact build/run command
20. Known limitations, stubs, and risks

If something cannot be resolved cleanly, the response must state:
- what is known
- what was assumed
- what was stubbed
- what boundary remains uncertain

Where a preferred review artifact or per-core file is not needed for that
specific lift, the response must say so explicitly instead of inventing empty
files purely for ceremony.

# ----------------------------------------------------------------------
# 11. One-Sentence Completion Standard
# ----------------------------------------------------------------------

A core lift is not complete until it identifies the narrowest real core top,
the first logical memory boundary above board/PHY glue, all meaningful
clock/reset domains, all platform-policy wrappers, all required runtime
assets, the legal supported tuple statement, the retained module boundary inventory,
the simulation observability contract, the explicit acceptance checks for a
repeatable sim without hidden platform assumptions, and the intentionally
excluded platform/board glue required to preserve a clean core boundary.

