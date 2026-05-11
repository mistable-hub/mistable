# Mistable Source of Truth Map

Status: Draft v0.5
Role: Current repo truth map

---

## 1. Purpose

This document maps the current repository state so humans and coding agents do not guess which files own which facts.

It is downstream from:

    doc/master_design_statement.md
    doc/ROADMAP.md
    doc/bringup_ladder.md

The master design statement defines what Mistable is and must remain.

The roadmap defines where Mistable goes over time.

The bringup ladder defines what order work happens in.

This source-of-truth map describes current repo reality only.

It does not define:

    roadmap phases
    bringup order
    task/rung template structure
    agent workflow procedure
    active task authorization
    verification results for completed rungs

Those responsibilities belong to the appropriate documents in the document system.

---

## 2. Current Document Authority Stack

The current top-level authority files are:

    CLAUDE.md
        Claude Code entry point.
        Directs Claude Code to read AGENTS.md for all standing rules and authority.

    AGENTS.md
        Standing rules for coding and review agents.
        Entry point for agent behavior and authority discovery.

    doc/master_design_statement.md
        Root design identity.
        Defines what Mistable is and must remain.

    doc/ROADMAP.md
        Big-picture development phases.
        Defines where Mistable goes over time.

    doc/bringup_ladder.md
        Ordered proof rungs.
        Defines what order work happens in.

    doc/source_of_truth.md
        Current repo truth map.
        Describes current repository reality and known non-claims.

    doc/process/agent_workflow.md
        Agent session procedure.
        Defines session modes, authority reading order, classification-before-editing,
        handoff expectations, structured reporting, tool/capability boundaries,
        context budget, and stop conditions.

    doc/process/code_review.md
        Review procedure.
        Defines read-only review behavior, dirty-diff review expectations,
        protected-file checks, scope checks, acceptance-evidence checks,
        non-claim checks, generated-artifact checks, pre-commit concern categories,
        review output format, and review stop conditions.

    doc/TASKS/task_template.md
        Standard developer-directive shape.
        Defines how future task/rung packets should be written.
        Protected files list now includes itself.

    doc/multi_core_structure.md
        Frozen repository structure and long-term integration policy.
        Defines the intended framework/core/ecosystem/board/build-control structure.

    doc/core_lift_sim_contract.md
        Frozen simulation-first core lift contract.
        Defines how upstream cores are to be lifted into the simulation-first path.

These files describe the current authority system, project direction, current repo truth, and process structure.

They do not, by themselves, authorize implementation.

Active implementation authority must come from a reconciled task/rung file under:

    doc/TASKS/

---

## 3. Current Agent Entry Points

The current repository contains two agent entry point files:

    CLAUDE.md
        Claude Code and similar assistant entry point.
        Thin file that points to AGENTS.md as the authority source.
        Does not duplicate AGENTS.md content.

    AGENTS.md
        Standing entry point for all coding and review agents.

Current reality:

    CLAUDE.md exists and is committed
    AGENTS.md has been reconciled with the current document system
    AGENTS.md references the master design statement, roadmap, bringup ladder,
    source-of-truth map, process documents, and task template
    AGENTS.md requires active task/rung authorization before implementation work
    AGENTS.md treats historical task files as pending reconciliation
    AGENTS.md preserves tool/capability boundaries and non-claims discipline

Current treatment:

    CLAUDE.md is the entry point for Claude Code sessions
    AGENTS.md is the first file all coding and review agents should read
    neither file is the whole project spec
    neither file must duplicate or replace downstream authority documents

Non-claims:

    CLAUDE.md does not authorize implementation by itself
    AGENTS.md does not authorize implementation by itself

---

## 4. Current Historical Task Files

The current repository contains historical task files under:

    doc/TASKS/

Current known historical task files:

    doc/TASKS/000_phase0_minimal_spine.md
    doc/TASKS/001_container_first_runner.md
    doc/TASKS/002_phase1_rp2350_pizero_appliance.md

Current treatment:

    these task files predate the current master-design / roadmap / bringup-ladder system
    they may describe completed work, useful historical intent, or out-of-sequence future work
    they are pending reconciliation
    they are not automatically current active authority

A historical task becomes active only when:

    it is reviewed against doc/master_design_statement.md
    it is reviewed against doc/ROADMAP.md
    it is reviewed against doc/bringup_ladder.md
    it is updated or replaced as needed
    a human project owner explicitly names it as the active task/rung

Known concern:

    doc/TASKS/002_phase1_rp2350_pizero_appliance.md describes physical RP2350 appliance work
    physical appliance work is out of sequence under the current roadmap until the virtual-board path is proven
    this task should be deferred or reconciled later, not executed now

---

## 5. Current Task Template

The current repository contains:

    doc/TASKS/task_template.md

Current role:

    standard developer-directive shape for future task/rung files

Current reality:

    task/rung template exists
    protected files list in §8 now includes doc/TASKS/task_template.md itself
    future task packets should be derived from this template unless a human project
    owner explicitly authorizes otherwise

Non-claims:

    doc/TASKS/task_template.md does not authorize implementation by itself
    doc/TASKS/task_template.md does not make historical tasks current
    doc/TASKS/task_template.md does not replace active task/rung packets

---

## 6. Current Verification Records

The current verification records under:

    doc/VERIFICATION/

Current known verification files:

    doc/VERIFICATION/document_control_stack_baseline.md
    doc/VERIFICATION/rung5.md

Current roles:

    doc/VERIFICATION/document_control_stack_baseline.md
        documentation-only baseline record confirming the document-control stack
        is present, role-consistent, and ready to govern future work

    doc/VERIFICATION/rung5.md
        formal Rung 5 verification record for the existing deterministic simulation spine
        records branch, HEAD, commands run, artifact info, golden hash comparison,
        what is proven, what is not proven, and next safe candidate

Current reality:

    doc/VERIFICATION/ contains two records
    document_control_stack_baseline.md is a documentation-only record
    rung5.md is the formal simulation spine verification record
    Rung 5 is complete

Non-claims:

    doc/VERIFICATION/document_control_stack_baseline.md does not verify RTL behavior
    doc/VERIFICATION/document_control_stack_baseline.md does not verify make sim
    doc/VERIFICATION/document_control_stack_baseline.md does not verify scripts/test.sh

---

## 7. Current Implementation Baseline

The current implementation baseline is the existing deterministic simulation spine.

Current implementation files:

    rtl/mistable_top.sv
    sim/tb.cpp
    sim/frame.ppm.sha256

Current roles:

    rtl/mistable_top.sv
        Current minimal RTL top.
        Produces deterministic video-like output for the simulation spine.

    sim/tb.cpp
        Current C++ simulation harness.
        Drives the RTL simulation and writes the output artifact.

    sim/frame.ppm.sha256
        Golden checksum for the current simulation artifact.
        Used by scripts/test.sh to detect unintended output changes.

Current generated artifact:

    build/frame.ppm

Current role of generated artifact:

    observable output produced by the current simulation spine
    binary PPM image
    used as the current deterministic smoke artifact

Non-claims:

    the current simulation spine is not a full virtual board
    the current simulation spine is not a monitor/service-link system
    the current simulation spine is not a multi-core framework
    the current simulation spine is not a real upstream core lift
    the current simulation spine is not physical-board ready

---

## 8. Current Build and Control Files

The current visible build/control entry point is:

    Makefile

Current known Make targets:

    make sim
    make clean
    make shell
    make sanity
    make golden

Current roles:

    make sim
        Builds and runs the current Verilator simulation.

    make clean
        Removes generated build output.

    make shell
        Enters the trusted container shell through ./dev.

    make sanity
        Runs ./scripts/sanity.sh.

    make golden
        Refreshes the golden smoke hash through UPDATE_GOLDEN=1 ./scripts/test.sh.

Current non-claim:

    the Makefile does not yet express the future CORE/ECOSYSTEM/BOARD tuple model

The tuple model belongs to later structure-migration rungs.

---

## 9. Current Container and Environment Files

The current container and environment files are:

    container/Dockerfile
    dev
    scripts/docker.sh
    scripts/bashrc
    scripts/sanity.sh

Current roles:

    container/Dockerfile
        Defines the current development container/tool environment.

    dev
        Convenience entry point for entering the trusted container shell.

    scripts/docker.sh
        Current Docker runner.
        Builds/uses the mistable-dev image and mounts the repo at /work.

    scripts/bashrc
        Shell defaults for interactive container sessions.

    scripts/sanity.sh
        Environment and repo sanity gate.
        Checks expected tools, repo contract, write access, git visibility, and simulation health.

Current important behavior:

    scripts/sanity.sh expects to run inside /work
    scripts/sanity.sh requires Verilator and core command-line tools
    scripts/sanity.sh checks current Phase 0 repo contract files

Current non-claim:

    the container workflow does not prove future virtual board behavior
    the container workflow does not prove future core-lift behavior
    the container workflow does not prove physical-board readiness

---

## 10. Current Test and Verification Files

The current test entry point is:

    scripts/test.sh

Current role:

    authoritative current smoke verification script for the existing simulation spine

Current behavior:

    cleans previous build output
    builds the simulation through make sim
    runs the simulation
    checks that build/frame.ppm exists
    computes the artifact SHA-256
    compares it against sim/frame.ppm.sha256
    prints PASS when the artifact matches the golden hash

Current golden-update path:

    UPDATE_GOLDEN=1 ./scripts/test.sh
    make golden

Current verification status:

    the repo has a working smoke verification path
    the smoke verification path has not yet been recorded as a formal Rung 5 verification record

Non-claim:

    scripts/test.sh is not yet a formal Rung 5 verification record

The first formal simulation spine verification record belongs to Rung 5.

---

## 11. Current Documentation Files

Current root/project documentation:

    README.md
    LICENSE
    .gitignore

Current roles:

    README.md
        Describes the current Phase 0 baseline, container workflow, simulation artifact,
        and long-term project direction.

    LICENSE
        Project license file.

    .gitignore
        Ignore rules for generated/local files.

Current reality:

    README.md still reflects the existing Phase 0 baseline and long-term structure direction
    README.md may need later updates as the new document system becomes active

Non-claim:

    README.md is not the root design authority
    README.md is not the bringup ladder
    README.md is not the active task authority

---

## 12. Current Frozen Architecture Documents

The current frozen architecture/policy documents are:

    doc/multi_core_structure.md
    doc/core_lift_sim_contract.md

Current roles:

    doc/multi_core_structure.md
        Frozen long-term repository structure and integration policy.
        Defines the intended layered structure for framework, cores, ecosystems,
        boards, external upstream cores, and build/control.

    doc/core_lift_sim_contract.md
        Frozen simulation-first upstream core lift contract.
        Defines how real upstream cores should be audited, wrapped, integrated,
        and reviewed for simulation-first use.

Current reality:

    these documents already exist
    the current repo is not yet fully migrated into the structure described by
    doc/multi_core_structure.md
    real core-lift work should not proceed until the required structural rungs are reached

Non-claim:

    existence of these documents does not mean the repo already implements the final structure
    existence of these documents does not mean a real core lift has started

---

## 13. Current Process Documents

The current process document state is:

    doc/process/agent_workflow.md
        Exists.
        Defines agent session modes, authority reading order, classification-before-editing,
        handoff expectations, structured reporting, tool/capability boundaries,
        one-active-implementation-agent policy, context budget rule, historical task handling,
        and stop conditions.

    doc/process/code_review.md
        Exists.
        Defines read-only review behavior, dirty-diff review expectations,
        protected-file checks, scope checks, acceptance-evidence checks,
        non-claim checks, generated-artifact checks, pre-commit concern categories,
        review output format, and review stop conditions.

Non-claims:

    doc/process/agent_workflow.md does not authorize implementation by itself
    doc/process/agent_workflow.md does not replace active task/rung files
    doc/process/code_review.md does not authorize implementation by itself
    doc/process/code_review.md does not replace active task/rung files

---

## 14. Current Missing Planned Documents

The current document system no longer has missing planned documents in the core stack.

The current document system has no missing planned documents in the core stack.

All planned verification records through Rung 5 now exist:

    doc/VERIFICATION/document_control_stack_baseline.md
        exists — document-control stack baseline

    doc/VERIFICATION/rung5.md
        exists — formal Rung 5 simulation spine verification record

Future verification records will be created as later rungs are executed.

---

## 15. What Is Currently Proven

The current repo proves, at most:

    there is an existing minimal deterministic simulation spine
    the simulation can produce an observable build artifact
    the repo has a Docker-oriented development environment
    the repo has Make/script entry points for current smoke verification
    the repo has a golden hash file for the current frame artifact
    the project has a root design statement, roadmap, bringup ladder, and source-of-truth map
    the project has a reconciled AGENTS.md and a CLAUDE.md entry point
    the project has agent workflow, code review procedure, and task template documents
    the project has frozen long-term structure and core-lift policy documents
    the document-control stack is present and role-consistent per
    doc/VERIFICATION/document_control_stack_baseline.md
    the existing deterministic simulation spine is formally verified per
    doc/VERIFICATION/rung5.md
    Rungs 0 through 5 are complete

This is the current baseline.

---

## 16. What Is Not Currently Proven

The current repo does not yet prove:

    full virtual board behavior
    working monitor behavior
    bounded service/event transport
    FPGA/MCU service-link behavior
    CORE/ECOSYSTEM/BOARD tuple implementation
    migration into the frozen multi-core structure
    real upstream core lift
    NES compatibility
    physical FPGA board support
    RP2350 appliance readiness
    Keystone86 PC integration
    multi-ecosystem support
    multi-board support
    fully reconciled historical task files

These items belong to later rungs.

---

## 17. Current Next Position

Rungs 0 through 5 are complete.

The next active work is:

    Rung 6: Repository Structure Migration Planning

This source-of-truth map does not itself start that work.

A future active task/rung file or explicit human instruction must authorize that work.

---

## 18. Conflict Rule

If this source-of-truth map conflicts with:

    AGENTS.md
    doc/master_design_statement.md
    doc/ROADMAP.md
    doc/bringup_ladder.md
    doc/multi_core_structure.md
    doc/core_lift_sim_contract.md
    doc/process/agent_workflow.md
    doc/process/code_review.md
    doc/TASKS/task_template.md

stop and resolve the conflict explicitly.

Do not silently reinterpret authority documents.

Do not use this map to override higher-authority design, roadmap, ladder, structure,
core-lift, process, agent, or task-template documents.

---

## 19. One-Sentence Summary

The current Mistable repo truth is a working deterministic simulation spine plus a
complete document-control authority system covering design identity, roadmap, bringup
ladder, agent rules, workflow, review, task template, and verification records through
Rung 5, with Rungs 0-5 complete and Rung 6 repository structure migration planning
as the next active work.
