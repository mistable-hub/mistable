# Task Packet: <task_name>

Status: Template  
Role: Standard developer directive shape

---

## 1. Purpose

Describe the specific purpose of this task.

This section must answer:

    What is this task meant to accomplish?
    Why does this task exist in the bringup ladder?
    What should be true after this task is complete?

Keep this section narrow.

Do not use this section to redefine roadmap phases, architecture, bringup order, source-of-truth mapping, or agent workflow.

---

## 2. Authority

Read and follow:

    AGENTS.md
    doc/master_design_statement.md
    doc/ROADMAP.md
    doc/bringup_ladder.md
    doc/source_of_truth.md
    doc/process/agent_workflow.md
    doc/process/code_review.md

Also read any task-specific authority listed here:

    <additional_authority_file_if_needed>

This task packet narrows the work for this task only.

It must not redefine Mistable architecture, roadmap direction, bringup order, source-of-truth mapping, or agent workflow procedure.

If this task conflicts with higher-authority documents, stop and report the conflict.

---

## 3. Bringup Ladder Position

This task corresponds to:

    Rung <N>: <rung_name>

From:

    doc/bringup_ladder.md

This task may implement only the work needed for this rung.

Do not start future-rung work.

Do not use this task to repair unrelated historical task drift unless explicitly authorized.

---

## 4. Mode

This task is a:

    <planning | implementation | review | verification | handoff>

The agent must follow the matching mode rules in:

    doc/process/agent_workflow.md

If this is a review task, the agent must also follow:

    doc/process/code_review.md

Do not mix modes unless this task explicitly authorizes it.

---

## 5. Starting Branch

Use the branch named by the invoking prompt.

Do not create, switch, merge, rebase, or delete branches unless the invoking prompt explicitly instructs you to do so.

Run first:

    git status --short
    git rev-parse --abbrev-ref HEAD
    git rev-parse HEAD

If the working tree is dirty before starting, stop and report the existing changes unless the invoking prompt explicitly says to continue from a dirty tree.

---

## 6. Required Initial Review

Before making changes, read the required authority documents and inspect the current files relevant to this task.

At minimum, confirm:

    active branch
    current HEAD
    working tree status
    required authority files exist
    allowed files exist or may be created
    protected files are not being edited unless authorized

Do not rely on prior chat history as authority.

Do not rely on agent memory as authority.

---

## 7. Allowed Files

This task may create or edit only:

    <allowed_file_or_directory>
    <allowed_file_or_directory>

If the task appears to require editing files outside this list, stop and report the reason.

Do not expand allowed files by inference.

---

## 8. Protected Files

Do not edit these files unless this task explicitly allows it:

    AGENTS.md
    doc/master_design_statement.md
    doc/ROADMAP.md
    doc/bringup_ladder.md
    doc/source_of_truth.md
    doc/process/agent_workflow.md
    doc/process/code_review.md
    doc/TASKS/task_template.md
    doc/multi_core_structure.md
    doc/core_lift_sim_contract.md

Additional protected files for this task:

    <additional_protected_file_if_needed>

If a protected file appears to require modification, stop and report the reason.

---

## 9. Forbidden Scope

Do not add, edit, or implement:

    <forbidden_scope_item>
    <forbidden_scope_item>

Common forbidden scope examples:

    future-rung work
    unrequested framework abstraction
    unrequested physical-board support
    unrequested MCU firmware
    unrequested service-link implementation
    unrequested core lift
    unrequested Verilator harness rewrite
    unrequested build-system redesign
    unrequested README expansion
    unrequested protected-file edits

This task must not become a general cleanup pass.

---

## 10. Required Work

Implement only the following:

    <required_work_item>
    <required_work_item>

Keep the implementation minimal and directly tied to the task purpose.

Do not implement optional future improvements.

Do not infer additional features from roadmap direction.

---

## 11. Required Non-Claims

This task must not claim:

    <non_claim>
    <non_claim>

Common non-claim examples:

    full virtual board behavior
    working monitor/debugger behavior
    FPGA interaction
    MCU equivalence
    service-link transport
    CORE/ECOSYSTEM/BOARD migration completion
    real upstream core support
    NES compatibility
    physical-board readiness
    Keystone86 PC readiness

Documentation, comments, final reports, and commit messages must preserve these non-claims.

---

## 12. Acceptance Commands

Run the following commands:

    <acceptance_command>
    <acceptance_command>

If a command cannot be run, report why.

If a command fails, fix only issues within the authorized scope.

Do not spend more than the task-authorized number of attempts fixing the same failure.

If the same failure remains after the allowed attempts, stop and report the blocker.

---

## 13. Review Requirements

Before reporting completion, inspect the final diff.

Run, when applicable:

    git status --short
    git diff --stat
    git diff --check

If this task involves code or scripts, inspect the relevant diff manually.

If this task involves documentation, confirm the changed document did not take over another document's role.

If this task involves generated artifacts, confirm they were authorized.

---

## 14. Commit Rules

Do not commit unless the invoking prompt explicitly requests a commit.

If committing is requested, commit only after required acceptance commands pass or after the task explicitly allows documentation/status-only commits without command success.

Suggested commit message:

    <type>: <short summary>

Do not push unless explicitly instructed.

---

## 15. Stop Conditions

Stop and report instead of guessing if:

    required authority files are missing
    the active task conflicts with higher-authority documents
    the working tree is dirty before starting and continuation was not authorized
    the task requires files outside the allowed list
    the task requires protected-file edits not explicitly authorized
    the task requires future-rung work
    the task requires architecture changes not authorized here
    acceptance cannot be proven
    required commands fail after the allowed number of attempts
    the same error repeats after the allowed number of fix attempts
    the branch or HEAD cannot be identified

Stopping and reporting is preferred over inventing architecture.

---

## 16. Required Final Report

At the end of the task, report:

    Branch:
    HEAD:
    Working tree status:
    Files changed:
    Commands run:
    Pass/fail result:
    Implemented scope:
    Explicit non-claims:
    What was not implemented:
    Known blockers:
    Next safe candidate:

The final report must be factual.

Do not overclaim.

Do not describe future work as completed.

---

## 17. Success Definition

This task is successful only if:

    only allowed files were changed
    protected files were not modified without authorization
    required work was completed
    forbidden scope was not implemented
    required acceptance commands passed or authorized exceptions were reported
    non-claims were preserved
    final report was provided in the required format

---

## 18. One-Sentence Summary

This task packet defines one bounded developer directive; it authorizes only the stated work for the named rung and does not permit architecture, roadmap, process, or future-rung expansion by inference.
