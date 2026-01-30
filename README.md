# 🚀 System Responsiveness Guard (SRG)

**Preventing System Slowdowns Caused by Resource-Hungry Processes**

System Responsiveness Guard (SRG) is a kernel-assisted monitoring and control mechanism designed to detect processes that degrade overall system responsiveness and apply safe, reversible constraints to restore interactivity — without terminating any process.

This project addresses a common real-world issue where systems become sluggish even though CPU and memory resources appear sufficient, typically due to aggressive background workloads starving interactive tasks.

# 📌 Problem Statement

Modern operating systems prioritize fairness in CPU scheduling but do not explicitly guarantee user-perceived responsiveness. As a result:

A single CPU-hogging process can make the system lag.

Interactive applications become slow or unresponsive.

Multi-user systems become difficult to use under load.

SRG introduces a lightweight kernel-level mechanism that:

Monitors per-process scheduling behavior.

Detects disruptive processes.

Dynamically applies non-destructive controls.

Restores normal behavior once stability returns.

# 🎯 Goals

Protect interactive responsiveness.

Avoid killing or crashing processes.

Require minimal kernel modifications.

Use simple, explainable detection logic.

Work on standard Linux kernels.

# 🏗️ System Architecture
+----------------------+
| User Workloads      |
| (stress, builds)    |
+----------+-----------+
           |
           v
+----------------------+
| SRG Kernel Module   |
|  - Monitoring       |
|  - Detection        |
|  - Control Engine   |
+----------+-----------+
           |
           v
+----------------------+
| Linux Scheduler     |
| (CFS + cgroups +    |
|  nice values)       |
+----------------------+

# 🔍 Kernel-Level Monitoring

SRG periodically scans all running processes and records:

Total CPU runtime

Context switch counts

Scheduling priority

Execution state

From these values, SRG computes:

CPU usage per interval

Frequency of yielding

Run vs wait behavior

This data allows SRG to infer which processes are monopolizing CPU.

# 🧠 Detection Logic

A process is considered disruptive if:

It consumes high CPU within a short interval.

It exhibits very low context switching.

This pattern persists for multiple consecutive intervals.

## Rule (Simplified)
If (CPU_usage > CPU_THRESHOLD)
AND (context_switches < CTX_THRESHOLD)
for N intervals
→ Mark as disruptive


This rule is:

Deterministic

Explainable

Low overhead

No machine learning or black-box heuristics are used.

# 🎛️ Control Mechanism

## When a disruptive process is detected, SRG applies temporary and reversible controls:

Possible Controls

Increase nice value (lower priority)

Move process to CPU-limited cgroup

Restrict CPU affinity

## Restoration

If the process behavior normalizes, SRG restores:

Original priority

Original CPU access

Processes are never terminated.

# 🔁 State Model
NORMAL → THROTTLED → NORMAL

# 🛡️ Safety Features

No kernel scheduler rewrite.

Rate-limited control actions.

Ignores kernel threads.

Never modifies PID 1.

Bounded memory usage.

Safe failure behavior.

# 🧪 Demonstration
## Before SRG
yes > /dev/null


Observe:

CPU at 100%

Terminal lag

Slow UI response

## After SRG
sudo insmod srg.ko


Observe:

CPU hog is throttled

Interactive shell responsive

Background process still running

# 📊 Example Output
PID    CPU(ms)   CTX   STATE
2314   850       2     THROTTLED
1142   45        60    NORMAL

# 📁 Repository Structure
System-Responsiveness/
 ├── src/
 │   └── srg_module.c
 ├── scripts/
 │   └── demo.sh
 ├── README.md
 └── report.md

# ⚙️ Build & Run
make
sudo insmod srg.ko
dmesg | tail


## To remove:

sudo rmmod srg

# 🚧 Current Status

Monitoring: Implemented / Prototype

Detection: Implemented

Control: Prototype

Full kernel module: Proof-of-concept

This project focuses on demonstrating feasibility and correctness rather than production readiness.

# 🔮 Future Work

Integrate with eBPF

Add cgroup v2 support

Per-user responsiveness policies

Visualization tools

# 👨‍💻 Authors

Team: Kinetic Koders
