# TASK 002 — Phase 1: RP2350-PiZero appliance layer (DVI + CDC + PIO-USB KB + SD splash + OSD)

**YOU ARE CODEX.**

**DO NOT ASK QUESTIONS. DO NOT GUESS. DO NOT ADD FEATURES. DO NOT CHANGE PINS.**  
**YOU MUST NOT MODIFY THE ORIGINAL DEFAULT BRANCH (main/master). ALL WORK MUST BE DONE ON A FEATURE BRANCH AND SUBMITTED AS A PULL REQUEST.**

**PHASE 1 ONLY. NO FPGA. NO AUDIO. NO EDID/DDC. NO CEC. NO HPD. NO MOUSE. NO JOYPADS.**  
**GOAL: WORKS RIGHT OUT OF THE GATE.**

---

## 0) PURPOSE / ACCEPTANCE

Deliver a Phase 1 firmware “appliance” for Waveshare RP2350-PiZero:

**Must-haves only:**
1. **DVI-over-HDMI** output on mini-HDMI:
   - **640x480p60** only
   - **colorbars + visible frame counter**
   - stable for **10 minutes** without dropout
2. **USB CDC ACM** logging over **PRIMARY USB-C** (native USB device)
3. **USB HOST HID keyboard** over **SECOND USB-C** using **PIO-USB** (GPIO46/47)
4. **OSD overlay** toggled by **F12**, composited during scanout, applied only at VSYNC boundary
5. **microSD mount (FAT)** via **SPI mode** (spi0), load `/splash.raw`:
   - `splash.raw` = **RGB565** **320x240 EXACT**
   - display scaled **2x** to **640x480**
   - if SD missing: remain on test pattern; log error

**Optional: NONE.** No CLI in Phase 1.

---

## A) GIT / PR WORKFLOW (MANDATORY FIRST STEPS)

1) Detect the repo default branch:
- If `main` exists use `main`, else if `master` exists use `master`.

2) Ensure you are on the default branch and it is clean:
- `git status` must show no uncommitted changes.
- If there are uncommitted changes, DO NOT DISCARD THEM:
  - create a WIP stash:
    - `git stash push -u -m "WIP before phase1 rp2350 pizero"`

3) Pull latest default branch:
- `git pull --rebase origin <default-branch>`

4) Create a new feature branch from default branch:
- Branch name MUST be: `phase1/rp2350-pizero-appliance`
- `git checkout -b phase1/rp2350-pizero-appliance`

5) All commits must be on this feature branch.

---

## B) PHASE 1 MUST-HAVES (ONLY THESE)

(1) DVI-over-HDMI video output on mini-HDMI:
- REQUIRED mode: 640x480p60
- REQUIRED pattern: colorbars + visible frame counter

(2) USB CDC ACM logging over PRIMARY USB-C:
- must enumerate and log continuously

(3) USB HOST keyboard over SECOND USB-C PIO-USB port:
- HID keyboard only

(4) OSD overlay toggled by F12:
- composited during scanout (scanline overlay)
- applied only at VSYNC boundary

(5) microSD mount (FAT) using SPI mode (spi0) and load `/splash.raw`:
- splash.raw RGB565 320x240 EXACT, display 2x scaled to 640x480
- if SD not present: keep test pattern; log error

Optional: NONE.

---

## C) NON-NEGOTIABLE ARCHITECTURE RULES

A) Use FreeRTOS from the beginning.

B) Video scanout MUST NOT be an RTOS task:
- video must be PIO + DMA driven with bounded IRQ
- no malloc/free in video engine
- no logging from video IRQ
- no blocking in video IRQ

C) Logging must be responsive:
- ring buffer logger drained by a task to CDC

D) OSD is scanline overlay:
- do not allocate a full framebuffer
- you may use a small scanline buffer

E) SD I/O must not stall video:
- SD reads in storage task; chunked reads (4KB or 8KB)

---

## D) BOARD PINS — EXACT (DO NOT CHANGE)

Create `src/board_pins.h` with EXACT definitions below.  
All modules must use ONLY these macros.  
Add compile-time `#error` checks in `board_pins.h` confirming each macro equals the expected literal value.

### DVI TMDS (mini-HDMI)
```c
#define PIN_DVI_D2_P    32
#define PIN_DVI_D2_N    33
#define PIN_DVI_D1_P    34
#define PIN_DVI_D1_N    35
#define PIN_DVI_D0_P    36
#define PIN_DVI_D0_N    37
#define PIN_DVI_CLK_P   39
#define PIN_DVI_CLK_N   38
```

### DVI sidebands present but NOT USED (MUST remain disabled)
```c
#define PIN_DVI_SDA     44
#define PIN_DVI_SCL     46
#define PIN_DVI_CEC      6
```

**Conflict rule (MANDATORY):**
- GPIO46 is used for PIO-USB DP; therefore DVI DDC/EDID MUST NOT be used.
- Do not initialize I2C for DVI. Do not attempt EDID. Do not touch CEC.

### microSD SPI (spi0)
```c
#define SD_SPI_INSTANCE spi0
#define PIN_SD_SCK      30
#define PIN_SD_MOSI     31
#define PIN_SD_MISO     40
#define PIN_SD_CS       43
```

### PIO-USB Host (SECOND USB-C)
```c
#define PIN_PIO_USB_DP  46
#define PIN_PIO_USB_DM  47
```

### Native USB CDC (PRIMARY USB-C)
- use native USB device controller; no GPIO mapping required.

### BOOT-TIME PIN PRINT (MANDATORY)
At boot, print a "PIN MAP" block to CDC listing all pins above and explicitly state:  
`DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP.`

---

## E) IMPLEMENTATION ANCHOR (MANDATORY — NO INVENTING FROM SCRATCH)

Use Waveshare’s RP2350-PiZero demo bundle as the baseline reference for:
- DVI output (their “01-DVI” demo approach/structure) on GPIO32–39
- PIO-USB host keyboard (their PIO-USB demo approach/structure) on GPIO46/47

Adapt those demos into THIS project layout, preserving correct low-level init and timing.

**Do not replace with a different DVI backend or a different USB-host stack if the Waveshare demo baseline exists.**  
If Waveshare baseline sources are not present locally, follow Section S4 deterministic selection rule; do NOT “mirror architecture” loosely.

---

## F) VIDEO REQUIREMENTS (MINIMUM)

Implement DVI over HDMI using a PicoDVI-style PIO + DMA TMDS output engine targeting the pins above.

REQUIRED output:
- 640x480p60 only (no other modes)
- colorbars pattern
- frame counter increments at VSYNC and is visible on screen

Stability requirement:
- Must run for 10 minutes without dropout (Phase 1 acceptance).

OSD overlay:
- toggled by F12 (default OFF at boot)
- draws small text block top-left:
  - `mistable OSD`
  - `SD: MOUNTED/NO`
  - `KB: OK/NO`
  - `UP: <seconds>`
- OSD overlays during scanout (scanline callback)
- OSD enable/disable must apply only at next VSYNC boundary (no tearing)

### Video module API (MUST EXIST)
```c
void video_init(void);
void video_set_source(int source); // SOURCE_TESTPATTERN or SOURCE_SPLASH
void video_request_osd_toggle(void); // pending toggle applied at VSYNC
uint32_t video_get_frame_counter(void);
```

---

## G) USB CDC LOGGING (MINIMUM)

USB CDC ACM must enumerate and print:
- boot banner: `mistable_phase1`
- build date/time
- heartbeat once per second

Implement ring-buffer logger + a `task_log_flush` task.

---

## H) USB HOST KEYBOARD (MINIMUM)

Implement USB host HID keyboard via PIO-USB on GPIO46/47.

Requirements:
- log connect/disconnect
- log key presses
- detect F12 -> request OSD toggle (apply at VSYNC boundary)
- hotplug must not crash
- if no keyboard present: continue and show `KB: NO` in OSD when enabled

---

## I) SD SPI + SPLASH (MINIMUM)

Mount FAT from SD via spi0.

If mount succeeds:
- attempt to open `/splash.raw`
- verify file size exactly 153600 bytes
- load to RAM (RGB565 320x240)
- set video source to splash (2x scaled to 640x480)

If any step fails:
- log error and remain on test pattern

SD performance rules:
- SD reads must be chunked (4KB or 8KB) in storage task
- do not perform SD I/O in video IRQ
- if SD mount fails, retry at most every 5 seconds

---

## J) FILE DEPENDENCIES — MUST BE GENERATED IN-REPO

You MUST generate all required non-source files in the repo so the developer can test immediately.

IMPORTANT:
- NEVER commit placeholder or zero-filled assets/sdcard.img. If not generated, do not create it.
- assets/sdroot.zip MUST be generated (always), even if mtools is not present.

1) Provide `tools/make_splash.py` (Python 3) that generates a valid `/splash.raw`:
- Output file path: `assets/sdroot/splash.raw`
- Format: RGB565 little-endian
- Size: 320x240 (exact)
- Content: deterministic pattern + text `MISTABLE PHASE1` rendered in pixels
- File must be exactly 153600 bytes.

2) Provide `tools/make_sd_image.py` (Python 3) that creates SD prep outputs:
REQUIRED (always):
- Produce `assets/sdroot.zip` containing:
  - `splash.raw` at filesystem root
  - `VERSION.TXT` at filesystem root

OPTIONAL (only if mtools present):
- Produce `assets/sdcard.img` as a FAT filesystem image containing the same root files.

Requirements:
- must NOT require root privileges
- must detect availability of mtools and gracefully fall back to only producing sdroot.zip
- must print clear instructions on success/failure

3) Provide `assets/sdroot/` containing at least:
- `splash.raw` (generated by tools/make_splash.py, committed into git)
- `VERSION.TXT` (committed)

4) Provide `scripts/prep_sd.sh`:
- If running on Linux with sudo available: detect SD device, format FAT32, copy contents of assets/sdroot to SD root.
- If sudo not available: print exact manual commands for user to run.
- MUST NOT auto-destroy disks without explicit confirmation prompt and clear device listing.

5) Provide a TESTING.md section that validates SD functions explicitly:
- show how to generate splash.raw and sdroot.zip (always)
- show how sdcard.img is produced (only if mtools present)
- show how to flash/copy to a real SD card
- pass/fail criteria for SD mount + splash display

If any tool dependency (mtools, mkfs.fat) is missing:
- scripts must detect this and print a clear instruction (install command) and a manual fallback
- do not fail silently

---

## K) FreeRTOS TASKS (MINIMUM)

Video engine is NOT a task.

Create only these tasks:
- `task_log_flush`: drains log ring buffer to CDC
- `task_usb_host`: runs PIO-USB host stack / polling
- `task_storage`: SD init/mount + splash load (one-shot at boot + periodic retry if missing)
- `task_status`: updates shared status struct for OSD (10 Hz)

Shared status struct fields:
- `uptime_seconds`
- `sd_state` (NO_CARD / MOUNT_FAIL / MOUNTED / SPLASH_OK / SPLASH_FAIL)
- `kb_state` (DISCONNECTED / CONNECTED)

---

## L) PROJECT STRUCTURE (MINIMUM)

Top-level (MUST EXIST):
- `CMakeLists.txt`
- `pico_sdk_import.cmake`
- `README.md`
- `TESTING.md`
- `LICENSE`
- `scripts/build.sh`
- `scripts/flash_uf2.txt`
- `scripts/prep_sd.sh`
- `scripts/lint_pins.sh`

`cmake/`
- `boards/`
  - `waveshare_rp2350_pizero.cmake` (ONLY if Pico SDK lacks a board for RP2350-PiZero)

`src/`
- `board_pins.h`
- `main.c`
- `FreeRTOSConfig.h` (REQUIRED)
- `log.c`
- `log.h`
- `status.c`
- `status.h`

`src/video/`
- `video_engine.c`
- `video_engine.h`
- `tmds_pio.c`
- `tmds_pio.h`
- `tmds.pio` (REQUIRED)
- `patterns.c`
- `patterns.h`
- `osd.c`
- `osd.h`
- `font8x8.c`
- `font8x8.h`
- `scale.c`
- `scale.h`

`src/usb/`
- `usb_device_cdc.c`
- `usb_device_cdc.h`
- `usb_host_piousb.c`
- `usb_host_piousb.h`
- `piousb_host.pio` (REQUIRED)
- `hid_keyboard.c`
- `hid_keyboard.h`

`src/storage/`
- `sd_spi.c`
- `sd_spi.h`
- `ff_port.c`
- `ff_port.h`
- `ffconf.h` (REQUIRED)
- `splash.c`
- `splash.h`

`assets/`
- `sdroot/`
  - `splash.raw`
  - `VERSION.TXT`
- `sdroot.zip` (REQUIRED; generated by make_sd_image.py and committed)
- `sdcard.img` (OPTIONAL; only if mtools present; never placeholder)

`tools/`
- `make_splash.py`
- `make_sd_image.py`
- `verify_assets.py`

`scripts/`
- `build.sh`
- `prep_sd.sh`
- `lint_pins.sh`
- `flash_uf2.txt`

`build_logs/`
- `README.md` (created and committed; updated on failures)
- `last_build_fail.txt` (created on first failure; updated thereafter)

`third_party/` (ONLY what is required by Sections E/Q/S; include licenses; no placeholders; no empty dirs)
- `README_THIRD_PARTY.md`
- `LICENSES/`
- `waveshare_demo/` (REQUIRED if using Waveshare baseline; see Section S)
- `PicoDVI_or_TMDS/` (REQUIRED only if Waveshare DVI demo sources are not available; see S4)
- `pico-sdk/` (REQUIRED unless repo already pins Pico SDK elsewhere; see S2)
- `FreeRTOS-Kernel/` (REQUIRED unless repo already vendors/submodules FreeRTOS elsewhere; see S3)
- `FatFS/` (ONLY if required by S6 path (b); otherwise do not vendor)

NOTES (MANDATORY):
- Do not create empty directories; each listed directory must contain at least one committed file.
- If a component is provided by Pico SDK or already exists in-repo, do NOT duplicate it; instead wire CMake to it.
- These files MUST exist so includes do not fail:
  - `pico_sdk_import.cmake`
  - `FreeRTOSConfig.h`
  - `ffconf.h`
  - `src/video/tmds.pio`
  - `src/usb/piousb_host.pio`

---

## M) BUILD REQUIREMENTS

- Use Pico SDK CMake style.
- Produce a UF2 file.
- README must include exact build commands:
  - `mkdir -p build && cd build`
  - `cmake .. -G Ninja`
  - `ninja`

- README must include flashing steps:
  - Enter BOOTSEL
  - Copy UF2 to the device mass storage

---

## N) TESTING.md MUST BE SIMPLE PASS/FAIL

M0: CDC enumerates and prints heartbeat 10 times.  
M1: HDMI shows stable colorbars + visible frame counter for 10 minutes.  
M2: Keyboard connects; key presses logged; F12 toggles OSD without glitch.  
M3: SD mounts; splash.raw loads and displays full-screen 640x480 (2x scale).  
M4: SD absent test: remove SD and confirm firmware continues with test pattern and logs mount failure.

---

## O) COMMIT / PUSH / PR REQUIREMENTS (MANDATORY)

You MUST:
1) Commit all added/changed files on the feature branch.
- Commit message MUST be: `Phase 1 RP2350-PiZero appliance layer`

2) Push the branch:
- `git push -u origin phase1/rp2350-pizero-appliance`

3) Create a PR:
- If GitHub CLI is available:
  - `gh pr create --base <default-branch> --head phase1/rp2350-pizero-appliance \`
    `--title "Phase 1: RP2350-PiZero appliance layer (DVI + CDC + PIO-USB KB + SD splash + OSD)" \`
    `--body "<include scope, build steps, test steps, out-of-scope list>"`

- If GitHub CLI is NOT available:
  - Print exact instructions to open a PR in the browser.

PR description MUST include:
- Scope: DVI 640x480p60 + CDC logs + PIO-USB keyboard + OSD + SD splash
- Build steps
- Test steps (M0–M4)
- Explicit Out-of-scope: FPGA ingest, audio, EDID/DDC, CEC, HPD, mouse, joypads

---

## P) OUTPUT REQUIREMENTS

Provide ALL files in full. No TODO placeholders. Build must compile.  
Do not add anything outside these requirements.

---

## Q) MISSING-DETAILS PATCH (MANDATORY TO AVOID MISINTERPRETATION)

### Q1) Pico SDK Board Definition (MANDATORY)
- If Pico SDK already contains a board definition for RP2350-PiZero, use it explicitly in scripts/build.sh via `-DPICO_BOARD=<name>`.
- Otherwise, create:
  - `cmake/boards/waveshare_rp2350_pizero.cmake`
  - and require scripts/build.sh to call:
    - `cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero`
- README.md must state the exact board name used.

### Q2) Pin Hygiene (MANDATORY)
- No source file may use raw GPIO numbers directly (e.g. `gpio_init(46)`).
- All GPIO references must come from `src/board_pins.h` macros only.
- Add `scripts/lint_pins.sh` that fails if it finds:
  - `GPIO[0-9]` or
  - `gpio_init(` with numeric literals
  outside `src/board_pins.h`.
- `scripts/build.sh` must run `scripts/lint_pins.sh`.

### Q3) Deterministic DVI dependency (MANDATORY)
- If Waveshare demo sources are not locally available, DO NOT invent a new DVI stack.
- Follow Section S4 deterministic selection rule.

### Q4) SD image generation fallback (MANDATORY)
- `tools/make_sd_image.py` must NOT require root privileges.
- Default behavior: ensure `assets/sdroot` contains `splash.raw` and `VERSION.TXT` and produce `assets/sdroot.zip`.
- If mtools is available: additionally produce `assets/sdcard.img`.
- TESTING.md must include both workflows:
  1) Copy `assets/sdroot/*` to a FAT SD card manually, or
  2) Use `sdcard.img` if produced.

### Q5) Asset verifier (MANDATORY)
Add `tools/verify_assets.py` that checks:
- `assets/sdroot/splash.raw` exists and size == 153600
- `assets/sdroot/VERSION.TXT` exists
- `assets/sdroot.zip` exists

`scripts/build.sh` must run `verify_assets.py` and print clear guidance if missing.

### Q6) Script executability (MANDATORY)
Ensure all scripts under `scripts/` are `chmod +x` and committed with executable bit.

### Q7) FatFS specifics (MANDATORY)
- Implement FatFS disk I/O with 512-byte sectors; read-only is acceptable for Phase 1.
- Include `ffconf.h` with minimal config for mount + file read.
- FatFS source selection is governed by Section S6.

### Q8) PIO source files must exist (MANDATORY)
Project MUST include committed PIO program sources referenced by the build:
- `src/video/tmds.pio`
- `src/usb/piousb_host.pio`

CMake must compile these via `pico_generate_pio_header()` or equivalent.

### Q9) Pico SDK import file must exist (MANDATORY)
Repo MUST contain `pico_sdk_import.cmake` at top-level so clean checkout can configure.

---

## R) BUILD-FAILURE HANDLING (MANDATORY “FIND, FIX, RESUME” LOOP)

Goal: if the build fails at any point, you MUST find the cause, correct it, and resume compiling until it succeeds.
You must NOT add features. You must ONLY make minimal changes required to fix the build and meet the already-stated requirements.

R0) Never ignore errors:
- no hand-waving, no stopping after first failure, no claiming success without clean build

R1) Always capture full logs when build fails:
1) Re-run failing command with verbose output:
- For configure:
  - `cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE`
- For build:
  - `ninja -v`
2) Save full output to:
- `build_logs/last_build_fail.txt` (commit it)
3) Append short summary to:
- `build_logs/README.md` including:
  - timestamp
  - command
  - first error line
  - fix applied (1–3 bullets)

R2) Classify failure (pick exactly one primary root cause):
A) Missing file in repo  
B) Wrong include path / include mismatch  
C) CMake wiring issue  
D) Third-party dependency missing/not wired  
E) Toolchain/environment issue  
F) Syntax/compile error in added file  

R3) Fix rules:
- fix only what error proves missing/miswired
- do not refactor
- do not change architecture/pins/capabilities
- smallest fix that keeps repo self-contained

R4) Missing-file policy (CRITICAL):
If build references a missing file, you MUST:
- add that file with complete non-placeholder content, OR
- adjust build to stop referencing it ONLY if task does not require it

R5) Submodules / vendoring handling:
- check:
  - `git submodule status`
- if submodules exist:
  - `git submodule update --init --recursive`
- if none or insufficient:
  - vendor minimal required code under `third_party/` and include licenses
- record in README under “Dependencies”

R6) CMake correction protocol:
- ensure every referenced `.c/.h/.pio` is in target sources OR generated correctly
- ensure include dirs are correct
- ensure scripts/build.sh runs:
  - scripts/lint_pins.sh
  - tools/verify_assets.py
  before build

R7) Resume loop:
- re-run failing command after each fix
- repeat until configure succeeds AND ninja produces UF2

R8) Clean build verification:
Before declaring success:
- `rm -rf build && mkdir build && cd build && cmake .. -G Ninja && ninja -v`
If it fails: not done; repeat loop.

R9) What to commit on failures:
- build_logs/last_build_fail.txt (updated each time)
- build_logs/README.md (append entries)
- minimal edits required to fix build

R10) Do not proceed to PR until build is green:
PR step must only happen after R8 passes.

---

## S) DETERMINISM ANCHORS (MANDATORY — ELIMINATE ALL GUESSING)

### S1) Waveshare demo baseline source location (MANDATORY WHEN USED)
If Waveshare RP2350-PiZero demo bundle is used as baseline, it MUST be committed under:
- `third_party/waveshare_demo/`

REQUIRED subpaths if baseline is used:
- `third_party/waveshare_demo/01-DVI/`
- `third_party/waveshare_demo/PIO-USB/`

`third_party/waveshare_demo/README.md` MUST include:
- exact upstream origin (URL)
- exact archive name/tag
- date retrieved
- if possible, commit hash or version identifier

Deterministic selection rule:
- If `third_party/waveshare_demo/01-DVI` exists, you MUST use Waveshare DVI baseline.
- If `third_party/waveshare_demo/PIO-USB` exists, you MUST use Waveshare PIO-USB baseline.

### S2) Pico SDK version pinning (MANDATORY)
Project MUST use a pinned Pico SDK revision.

Deterministic rule:
- Prefer Pico SDK as git submodule at: `third_party/pico-sdk/`
- If repo already contains a Pico SDK submodule elsewhere, use that location; do not duplicate.

README.md MUST state the exact Pico SDK commit SHA used.

scripts/build.sh MUST fail fast with clear message if:
- pinned SDK is not present AND `PICO_SDK_PATH` is not set

### S3) FreeRTOS kernel source pinning (MANDATORY)
FreeRTOS kernel sourcing MUST be deterministic:
- Prefer committed sources under: `third_party/FreeRTOS-Kernel/`
- If repo already vendors/submodules FreeRTOS elsewhere, use that and do not duplicate.

README.md MUST state exact source location and commit/tag if applicable.

### S4) DVI/TMDS implementation path selection (MANDATORY)
DVI/TMDS implementation MUST follow this deterministic choice:
(a) If `third_party/waveshare_demo/01-DVI` exists:
- use it as baseline and adapt into `src/video/`
(b) Else:
- vendor a known-good PicoDVI-style PIO+DMA TMDS engine under:
  - `third_party/PicoDVI_or_TMDS/`
- use that baseline (do not invent a new stack)

README.md MUST state which path (a) or (b) is used.

### S5) USB host threading model lock (MANDATORY)
USB host stack MUST run entirely inside `task_usb_host` as a polling loop.
USB-host related IRQ usage is limited to bounded PIO/DMA servicing only.
No USB-host logging or blocking operations in any IRQ context.

### S6) FatFS sourcing deterministic rule (MANDATORY)
FatFS source selection MUST follow:
(a) If Pico SDK provides usable FatFS integration: use it (do not vendor FatFS)
(b) Else: vendor FatFS under `third_party/FatFS/` with license included

README.md MUST state which path (a) or (b) is used and where sources come from.

---

## T) HARD GATES (MANDATORY — PREVENT “COMPILES BUT DOESN’T WORK”)

These checks MUST be implemented and enforced by `scripts/build.sh` (fail build if violated).

### T1) No stubs / no TODO placeholders in src/
Before build and after build, fail if any of the following appear in `src/`:
- `TODO`
- `FIXME`
- `stub`
- `not implemented`
- `return 0; /* TEMP` (or similar placeholder patterns)

EXCEPTION:
- none in `src/` (third_party excluded).  
This is to prevent placeholder modules that “compile”.

### T2) Required files existence + non-empty
Fail fast if any required file is missing or zero-length:
- `pico_sdk_import.cmake`
- `src/FreeRTOSConfig.h`
- `src/storage/ffconf.h`
- `src/video/tmds.pio`
- `src/usb/piousb_host.pio`
- `assets/sdroot/splash.raw`
- `assets/sdroot/VERSION.TXT`
- `assets/sdroot.zip`

### T3) PIO header generation must be wired
CMake MUST generate PIO headers for:
- `src/video/tmds.pio`
- `src/usb/piousb_host.pio`

Fail build if generated headers are not produced in the build directory.

### T4) Outputs must exist
After build, fail if UF2 is missing or empty:
- `<target>.uf2` must exist and be > 0 bytes
- `<target>.elf` must exist and be > 0 bytes

### T5) PR evidence requirement
PR body MUST include:
- exact build commands run
- confirmation of clean build (R8)
- copy/paste of CDC log for 10 seconds showing heartbeats

---

## END
