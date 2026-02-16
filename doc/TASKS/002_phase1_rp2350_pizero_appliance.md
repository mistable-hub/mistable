# TASK 002 — Phase 1: RP2350-PiZero appliance layer (DVI + CDC + PIO-USB KB + SD splash + OSD)

**YOU ARE CODEX.**

**DO NOT ASK QUESTIONS. DO NOT GUESS. DO NOT ADD FEATURES. DO NOT CHANGE PINS.**  
**YOU MUST NOT MODIFY THE ORIGINAL DEFAULT BRANCH (main/master). ALL WORK MUST BE DONE ON A FEATURE BRANCH AND SUBMITTED AS A PULL REQUEST.**

**PHASE 1 ONLY. NO FPGA. NO AUDIO. NO EDID/DDC. NO CEC. NO HPD. NO MOUSE. NO JOYPADS.**  
**GOAL: WORKS RIGHT OUT OF THE GATE.**

---

## A) GIT / PR WORKFLOW (MANDATORY FIRST STEPS)

1) Detect the repo default branch:
- If `main` exists use `main`, else if `master` exists use `master`.

2) Ensure you are on the default branch and it is clean:
- `git status` must show no uncommitted changes.
- If there are uncommitted changes, DO NOT DISCARD THEM:
  - create a WIP stash:  
    `git stash push -u -m "WIP before phase1 rp2350 pizero"`

3) Pull latest default branch:
- `git pull --rebase origin <default-branch>`

4) Create a new feature branch from default branch:
- Branch name MUST be: `phase1/rp2350-pizero-appliance`
- `git checkout -b phase1/rp2350-pizero-appliance`

5) All commits must be on this feature branch.

---

## B) PHASE 1 MUST-HAVES (ONLY THESE)

1) DVI-over-HDMI video output on the onboard mini-HDMI connector:
- REQUIRED mode: **640x480p60**
- REQUIRED test pattern: **colorbars + visible frame counter**

2) USB CDC ACM logging over PRIMARY USB-C (native USB device)

3) USB HOST keyboard input over SECOND USB-C PIO-USB port (**HID keyboard only**)

4) OSD overlay toggled by **F12** (MiSTer hotkey), composited during scanout

5) microSD mount (FAT) using **SPI mode (spi0)** and load `/splash.raw`
- `splash.raw` RGB565 **320x240 EXACT**, display **2x scaled** to 640x480  
If SD not present: keep test pattern; log error.

Optional: **NONE**. No CLI in Phase 1.

---

## C) NON-NEGOTIABLE ARCHITECTURE RULES

A) Use **FreeRTOS** from the beginning.  
B) Video scanout MUST NOT be an RTOS task.
- video must be **PIO + DMA** driven with bounded IRQ
- no malloc/free in video engine
- no logging from video IRQ
- no blocking in video IRQ

C) Logging must be responsive:
- ring buffer logger drained by a task to CDC

D) OSD is scanline overlay:
- do not allocate a full framebuffer
- you may use a small scanline buffer

E) SD I/O must not stall video:
- SD reads in storage task; chunked reads

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

### DVI sidebands present but NOT USED (and MUST remain disabled)
```c
#define PIN_DVI_SDA     44
#define PIN_DVI_SCL     46
#define PIN_DVI_CEC      6
```

Conflict rule (MANDATORY):
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

BOOT-TIME PIN PRINT (MANDATORY):
- At boot, print a "PIN MAP" block to CDC listing all pins above and explicitly state:  
  **"DVI DDC/EDID disabled because GPIO46 is used for PIO-USB DP."**

---

## E) IMPLEMENTATION ANCHOR (MANDATORY — NO INVENTING FROM SCRATCH)

Use Waveshare’s RP2350-PiZero demo bundle as the baseline reference for:
- DVI output (their “01-DVI” demo approach/structure) on GPIO32–39
- PIO-USB host keyboard (their PIO-USB demo approach/structure) on GPIO46/47

Adapt those demos into THIS project layout, preserving correct low-level init and timing.  
Do not replace with a different DVI backend or a different USB-host stack if the Waveshare demo baseline exists.

If Waveshare baseline sources are not present locally, follow Section S4 (deterministic DVI/TMDS selection); do NOT “mirror architecture” loosely.

---

## F) VIDEO REQUIREMENTS (MINIMUM)

Implement DVI over HDMI using a PicoDVI-style PIO + DMA TMDS output engine targeting the pins above.

REQUIRED output:
- 640x480p60 only (no other modes)
- colorbars pattern
- frame counter that increments at VSYNC and is visible on screen

Stability requirement:
- Must run for 10 minutes without dropout (Phase 1 acceptance).

OSD overlay:
- toggled by F12 (default OFF at boot)
- draws small text block top-left:
  - "mistable OSD"
  - "SD: MOUNTED/NO"
  - "KB: OK/NO"
  - "UP: <seconds>"
- OSD must overlay during scanout (scanline callback).
- OSD enable/disable must apply only at next VSYNC boundary (no tearing).

Video module API (must exist):
```c
void video_init(void);
void video_set_source(int source /* SOURCE_TESTPATTERN or SOURCE_SPLASH */);
void video_request_osd_toggle(void);   // sets a pending toggle applied at VSYNC
uint32_t video_get_frame_counter(void);
```

---

## G) USB CDC LOGGING (MINIMUM)

USB CDC ACM must enumerate and print:
- boot banner: "mistable_phase1"
- build date/time
- heartbeat once per second

Implement ring-buffer logger + a log_flush task.

---

## H) USB HOST KEYBOARD (MINIMUM)

Implement USB host HID keyboard via PIO-USB on GPIO46/47.

Requirements:
- log connect/disconnect
- log key presses
- detect F12 -> request OSD toggle (apply at VSYNC boundary)
- hotplug must not crash
- if no keyboard present: continue and show "KB: NO" in OSD when enabled

---

## I) SD SPI + SPLASH (MINIMUM)

Mount FAT from SD via spi0.

If mount succeeds:
- attempt to open `/splash.raw`
- verify file size exactly **153600 bytes**
- load to RAM (RGB565 320x240)
- set video source to splash (2x scaled to 640x480)

If any step fails:
- log error and remain on test pattern.

SD performance rules:
- SD reads must be chunked (4KB or 8KB) in storage task.
- do not perform SD I/O in video IRQ.
- If SD mount fails, retry at most every 5 seconds.

---

## J) FILE DEPENDENCIES — MUST BE GENERATED IN-REPO

You MUST generate all required non-source files in the repo so the developer can test immediately.

IMPORTANT:
- NEVER commit placeholder or zero-filled `assets/sdcard.img`. If not generated, do not create it.
- `assets/sdroot.zip` MUST be generated (always), even if mtools is not present.

1) Provide `tools/make_splash.py` (Python 3) that generates a valid `/splash.raw`:
- Output file path: `assets/sdroot/splash.raw`
- Format: RGB565 little-endian
- Size: 320x240 (exact)
- Content: a deterministic pattern + the text "MISTABLE PHASE1" rendered in pixels
- The file must be exactly 153600 bytes.

2) Provide `tools/make_sd_image.py` (Python 3) that creates SD prep outputs:

REQUIRED (always):
- Produce `assets/sdroot.zip` that contains the root files to copy to an SD card:
  - `splash.raw` at filesystem root
  - `VERSION.TXT` at filesystem root

OPTIONAL (only if mtools present):
- Produce `assets/sdcard.img` as a FAT filesystem image containing those same root files.

Requirements:
- must NOT require root privileges
- must detect availability of mtools and gracefully fall back to only producing sdroot.zip
- must print clear instructions on success/failure

3) Provide `assets/sdroot/` directory in the repo containing at least:
- `splash.raw` (generated by tools/make_splash.py, committed into git)
- `VERSION.TXT` (committed)

4) Provide `scripts/prep_sd.sh`:
- If running on Linux with sudo available: detect SD device, format FAT32, copy contents of assets/sdroot to SD root.
- If sudo not available: print exact manual commands for user to run.
- The script MUST NOT auto-destroy disks without explicit confirmation prompt and clear device listing.

5) Provide a `TESTING.md` section that validates SD functions explicitly:
- Show how to generate splash.raw and sdroot.zip (always)
- Show how sdcard.img is produced (only if mtools present)
- Show how to flash/copy to a real SD card
- Pass/fail criteria for SD mount + splash display

If any tool dependency (mtools, mkfs.fat) is missing:
- scripts must detect this and print a clear instruction (install command) and a manual fallback.
- Do not fail silently.

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
- `LICENSE` (project license, must exist)
- `scripts/build.sh` (builds project)
- `scripts/flash_uf2.txt` (text instructions, not a script)
- `scripts/prep_sd.sh` (see above)
- `scripts/lint_pins.sh`

```
cmake/
  boards/
    waveshare_rp2350_pizero.cmake   (ONLY if Pico SDK lacks a board for RP2350-PiZero)

src/
  board_pins.h
  main.c
  FreeRTOSConfig.h
  log.c
  log.h
  status.c
  status.h

  video/
    video_engine.c
    video_engine.h
    tmds_pio.c
    tmds_pio.h
    tmds.pio
    patterns.c
    patterns.h
    osd.c
    osd.h
    font8x8.c
    font8x8.h
    scale.c
    scale.h

  usb/
    usb_device_cdc.c
    usb_device_cdc.h
    usb_host_piousb.c
    usb_host_piousb.h
    piousb_host.pio
    hid_keyboard.c
    hid_keyboard.h

  storage/
    sd_spi.c
    sd_spi.h
    ff_port.c
    ff_port.h
    ffconf.h
    splash.c
    splash.h

assets/
  sdroot/
    splash.raw
    VERSION.TXT
  sdroot.zip
  sdcard.img   (OPTIONAL; only if mtools present; never placeholder)

tools/
  make_splash.py
  make_sd_image.py
  verify_assets.py

scripts/
  build.sh
  prep_sd.sh
  lint_pins.sh
  flash_uf2.txt

build_logs/
  README.md
  last_build_fail.txt

third_party/ (SUBMODULES ONLY — see Section S)
  README_THIRD_PARTY.md
  LICENSES/
  waveshare_demo/
  PicoDVI_or_TMDS/                  (ONLY if S4(b) path is used)
  pico-sdk/
  FreeRTOS-Kernel/
  FatFS/                            (ONLY if S6(b) path is used)
```

NOTES (MANDATORY):
- Do not create empty directories; each listed directory must contain at least one committed file.
- If a component is provided by Pico SDK or already exists in-repo, do NOT duplicate it; instead wire CMake to it.
- The files explicitly listed above (`pico_sdk_import.cmake`, `FreeRTOSConfig.h`, `ffconf.h`, `*.pio`) MUST exist so builds and includes do not fail.

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
- Commit message MUST be: **"Phase 1 RP2350-PiZero appliance layer"**

2) Push the branch:
- `git push -u origin phase1/rp2350-pizero-appliance`

3) Create a PR:
- If GitHub CLI is available:
  ```sh
  gh pr create --base <default-branch> --head phase1/rp2350-pizero-appliance \
    --title "Phase 1: RP2350-PiZero appliance layer (DVI + CDC + PIO-USB KB + SD splash + OSD)" \
    --body "<include scope, build steps, test steps, out-of-scope list>"
  ```
- If GitHub CLI is NOT available:
  - Print the exact instructions to open a PR in the browser.

PR description MUST include:
- Scope: DVI 640x480p60 + CDC logs + PIO-USB keyboard + OSD + SD splash
- Build steps
- Test steps (M0–M4)
- Explicit Out-of-scope items: FPGA ingest, audio, EDID/DDC, CEC, HPD, mouse, joypads

---

## P) OUTPUT REQUIREMENTS

Provide ALL files in full. No TODO placeholders. Build must compile.  
Do not add anything outside these requirements.

---

## Q) MISSING-DETAILS PATCH (MANDATORY TO AVOID MISINTERPRETATION)

### Q1) Pico SDK Board Definition (MANDATORY)
- If the Pico SDK already contains a board definition for RP2350-PiZero, use it explicitly in `scripts/build.sh` via `-DPICO_BOARD=<name>`.
- Otherwise, create a minimal custom board definition at:
  - `cmake/boards/waveshare_rp2350_pizero.cmake`
  and require `scripts/build.sh` to call:
  - `cmake .. -G Ninja -DPICO_BOARD=waveshare_rp2350_pizero`
- `README.md` must state the exact board name used.

### Q2) Pin Hygiene (MANDATORY)
- No source file may use raw GPIO numbers directly (e.g. `gpio_init(46)`).
- All GPIO references must come from `src/board_pins.h` macros only.
- Add `scripts/lint_pins.sh` that fails if it finds `GPIO[0-9]` or `gpio_init(` with numeric literals outside `src/board_pins.h`.
- `scripts/build.sh` must run `scripts/lint_pins.sh`.

### Q3) Deterministic DVI dependency (MANDATORY)
- If Waveshare demo sources are not locally available, DO NOT "invent" a new DVI stack.
- Follow Section S4 deterministic selection rule.

### Q4) SD image generation fallback (MANDATORY)
- `tools/make_sd_image.py` must NOT require root privileges.
- Default behavior: ensure assets/sdroot contains splash.raw and VERSION.TXT and produce assets/sdroot.zip.
- If mtools is available, additionally produce assets/sdcard.img containing those files at the filesystem root.
- TESTING.md must include both workflows:
  1) Copy assets/sdroot/* to a FAT SD card manually, or
  2) Use sdcard.img if produced.

### Q5) Asset verifier (MANDATORY)
- Add `tools/verify_assets.py` that checks:
  - assets/sdroot/splash.raw exists and size == 153600
  - assets/sdroot/VERSION.TXT exists
  - assets/sdroot.zip exists
- `scripts/build.sh` must run verify_assets.py and print clear guidance if missing.

### Q6) Script executability (MANDATORY)
- Ensure all scripts under scripts/ are chmod +x and committed with executable bit.

### Q7) FatFS specifics (MANDATORY)
- Implement FatFS disk I/O with 512-byte sectors and read-only is acceptable for Phase 1.
- Include `ffconf.h` with a minimal configuration suitable for mount + file read.
- FatFS source selection is governed by Section S6 (deterministic).

### Q8) PIO source files must exist (MANDATORY)
- The project MUST include committed PIO program source files referenced by the build:
  - `src/video/tmds.pio`
  - `src/usb/piousb_host.pio`
- CMake must compile these via `pico_generate_pio_header()` or equivalent Pico SDK mechanism.

### Q9) Pico SDK import file must exist (MANDATORY)
- The repo MUST contain `pico_sdk_import.cmake` at top-level so a clean checkout can configure without missing-file errors.

### Q10) SUBMODULE URL HYGIENE (MANDATORY — PREVENT NON-PORTABLE BUILDS)
- **Submodules are REQUIRED (preferred), and URLs MUST be public HTTPS git URLs.**
- `.gitmodules` MUST NOT contain:
  - `/tmp/...`
  - local filesystem paths
  - relative `../` paths
  - non-git URLs
- After adding or updating any submodule, you MUST run:
  - `git submodule update --init --recursive`
- `scripts/build.sh` MUST fail fast if required submodule directories exist but are empty, and print:
  - `git submodule update --init --recursive`

---

## R) BUILD-FAILURE HANDLING (MANDATORY “FIND, FIX, RESUME” LOOP)

Goal: If the build fails at any point, you MUST find the cause, correct it, and resume compiling until it succeeds.  
You must NOT add features. You must ONLY make the minimal changes required to fix the build and meet the already-stated requirements.

R0) Never ignore errors
- Do not hand-wave. Do not stop after the first failure. Do not claim success without a clean build.

R1) Always capture full logs  
When a build step fails, immediately:
1) Re-run the failing command with verbose output:
- For configure: `cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release --log-level=VERBOSE`
- For build: `ninja -v`
2) Save the full output to: `build_logs/last_build_fail.txt` (commit it)
3) Also append a short summary to: `build_logs/README.md`
- include: timestamp, command, first error line, and the fix applied (1–3 bullets)

R2) Classify the failure (pick exactly one primary root cause)  
You MUST identify which category the failure belongs to:
A) Missing file in repo (header/source/script/cmake/pio/asset)  
B) Wrong include path / include name mismatch  
C) CMake target wiring issue (file not added to target, missing library link, missing include dirs)  
D) Third-party dependency not present / not wired (FreeRTOS/TinyUSB/FatFS/PIO-USB/PicoDVI)  
E) Toolchain/environment issue (Pico SDK path, submodules not initialized, missing Ninja, missing Python)  
F) Syntax/compile error inside an added file

R3) Fix rules (minimal, deterministic)
- Fix only what the error proves is missing or miswired.
- Do not refactor.
- Do not change architecture, pins, or add new capabilities.
- If multiple fixes are possible, choose the smallest fix that keeps the repo self-contained.

R4) Missing-file policy (CRITICAL)
If the error indicates a missing file that the code/build references, you MUST:
- Add that file to the repo, with complete non-placeholder content, OR
- adjust the build to stop referencing it, ONLY if the task file does NOT require it.

R5) Submodules and vendoring handling (no guessing)
- **Submodules only (preferred and required by this task unless explicitly allowed otherwise).**
- If the build fails due to missing third_party code:
  1) Check submodules:
     - `git submodule status`
  2) Initialize/update:
     - `git submodule update --init --recursive`
  3) If a required upstream is not available as a git repo, create a mirror repo under the project org and use that HTTPS URL (see S1/S7).

R6) CMake correction protocol
If the failure is CMake wiring:
- Ensure every referenced .c/.h/.pio is either:
  - added to the correct target sources, OR
  - generated correctly by Pico SDK helpers (PIO headers), AND
  - include directories are set so headers resolve.
- Ensure `scripts/build.sh` runs:
  - `scripts/lint_pins.sh`
  - `tools/verify_assets.py`
  before build, and those steps must also pass.

R7) Resume loop (mandatory)
After applying a fix:
1) Re-run the same command that failed (configure or ninja -v).
2) If it fails again, repeat R1–R7.
3) Only stop when:
- cmake configure completes successfully, AND
- ninja completes successfully producing UF2.

R8) “Clean build” verification (mandatory)
Before declaring success:
- Delete build directory and rebuild from scratch:
  - `rm -rf build && mkdir build && cd build && cmake .. -G Ninja && ninja -v`
- If this fails, you are NOT done. Repeat the loop.

R9) Output requirements for failures (what to commit)
You MUST commit:
- build_logs/last_build_fail.txt (updated each time)
- build_logs/README.md (append entries)
- any minimal files/edits required to fix the build

R10) Do not proceed to PR until build is green
- PR creation step (section O) MUST only happen after R8 clean build passes.

---

## S) DETERMINISM ANCHORS (MANDATORY — ELIMINATE ALL GUESSING)

### S1) Waveshare demo baseline source location (MANDATORY WHEN USED)
- If the Waveshare RP2350-PiZero demo bundle is used as baseline, it MUST be present as committed sources under:
  - `third_party/waveshare_demo/`  (**as a git submodule**)
- The following subpaths are REQUIRED if Waveshare baseline is used:
  - `third_party/waveshare_demo/01-DVI/` (DVI demo sources)
  - `third_party/waveshare_demo/PIO-USB/` (PIO-USB host keyboard demo sources)
- `third_party/waveshare_demo/README.md` MUST exist and MUST include:
  - exact upstream origin (URL)
  - exact archive name or tag
  - date retrieved
  - if possible, commit hash or version identifier

Deterministic selection rule:
- If `third_party/waveshare_demo/01-DVI` exists, you MUST use the Waveshare DVI baseline (no alternatives).
- If `third_party/waveshare_demo/PIO-USB` exists, you MUST use the Waveshare PIO-USB baseline (no alternatives).

### S2) Pico SDK version pinning (MANDATORY)
- The project MUST use a pinned Pico SDK revision.
Deterministic rule:
- Prefer Pico SDK as a git submodule at: `third_party/pico-sdk/`
- If the repo already contains a Pico SDK submodule elsewhere, use that location; do not duplicate it.
- README.md MUST state the exact Pico SDK commit SHA used.
- scripts/build.sh MUST fail fast with a clear message if the pinned SDK is not present and PICO_SDK_PATH is not set.

### S3) FreeRTOS kernel source pinning (MANDATORY)
- FreeRTOS kernel sourcing MUST be deterministic:
  - Prefer FreeRTOS-Kernel as committed sources under: `third_party/FreeRTOS-Kernel/` (git submodule)
  - If the repo already vendors or submodules FreeRTOS elsewhere, use that and do not duplicate.
- README.md MUST state the exact source location and (if applicable) commit/tag used.

### S4) DVI/TMDS implementation path selection (MANDATORY)
- DVI/TMDS implementation MUST follow this deterministic choice:
  (a) If `third_party/waveshare_demo/01-DVI` exists: use it as baseline and adapt into `src/video/`.  
  (b) Else: vendor a known-good PicoDVI-style PIO+DMA TMDS engine under:
      `third_party/PicoDVI_or_TMDS/` (as a git submodule) and use that baseline (do not invent a new stack).
- README.md MUST clearly state which path (a) or (b) is in use.

### S5) USB host threading model lock (MANDATORY)
- The USB host stack MUST run entirely inside `task_usb_host` as a polling loop.
- USB-host related IRQ usage is limited to bounded PIO/DMA servicing only.
- No USB-host logging or blocking operations in any IRQ context.

### S6) FatFS sourcing deterministic rule (MANDATORY)
- FatFS source selection MUST follow this deterministic choice:
  (a) If Pico SDK provides a usable FatFS integration: use it (do not vendor FatFS).  
  (b) Else: include FatFS under `third_party/FatFS/` as a git submodule with license included.
- README.md MUST state which path (a) or (b) is used and where the sources come from (tag/version).

### S7) SUBMODULES-ONLY ENFORCEMENT (MANDATORY)
- All third_party dependencies required by this task MUST be provided via **git submodules**.
- If any upstream dependency is not available as a git repository (example: Waveshare demo bundle distributed as a zip),
  you MUST:
  1) create a mirror repository under the project’s GitHub org (e.g., `mistable-hub/…`), and
  2) add that mirror as the submodule via **public HTTPS git URL**, and
  3) record the upstream origin + archive name/date in `third_party/<name>/README.md`.

END.
