🛡️ System Responsiveness Guard

Preventing System Slowdowns Caused by Resource-Hungry Processes

📌 Overview

In real-world systems, users often experience lag, freezes, or unresponsiveness even when CPU and memory appear sufficient.
This happens when one or more aggressive processes monopolize CPU time, starving interactive or critical tasks.

System Responsiveness Guard is a lightweight Linux-based monitoring tool that demonstrates how system responsiveness can be observed, detected, and protected using OS-level scheduling behavior — without killing processes.

🎯 Problem Statement

Modern Linux schedulers prioritize fairness but not always user-perceived responsiveness.

Common issues include:

Background CPU-heavy tasks causing UI lag

Builds or scripts freezing shared machines

Interactive processes being starved under load

This project demonstrates:

How responsiveness degradation can be detected

How system behavior changes under CPU stress

A foundation for kernel-assisted control mechanisms

🧠 Key Idea

Instead of terminating processes, the system:

Continuously monitors scheduling delay

Detects responsiveness degradation

Warns when the system becomes less responsive

This aligns with real OS design goals: control, not destruction.

🏗️ Architecture (High Level)
+------------------------+
|  CPU-Heavy Process     |  --> yes > /dev/null
+------------------------+
            |
            v
+------------------------+
| Linux Scheduler (CFS)  |
+------------------------+
            |
            v
+------------------------+
| System Responsiveness  |
| Guard (Monitor)        |
| - Measures delays      |
| - Detects degradation  |
+------------------------+

🔍 What This Project Does
Monitoring

Measures scheduling delay using high-resolution timers

Observes how often the process is delayed by the scheduler

Detection

Uses simple, rule-based thresholds

Flags responsiveness degradation when delay exceeds limits

Control (Conceptual)

Demonstrates where corrective actions would be applied:

Priority reduction

CPU throttling

Core restriction

⚠️ No processes are killed.

🛠️ Tech Stack

Language: C

Platform: Linux (Tested on Ubuntu 22.04 via WSL2)

Tools: gcc, make

Stress Generator: yes > /dev/null

📂 Project Structure
resp_guard/
├── resp_guard.c     # Responsiveness monitoring logic
├── Makefile         # Build instructions
├── README.md        # Project documentation

🚀 How to Run
1️⃣ Clone the Repository
git clone https://github.com/your-username/system-responsiveness-guard.git
cd system-responsiveness-guard

2️⃣ Install Dependencies
sudo apt update
sudo apt install -y build-essential

3️⃣ Compile
make

4️⃣ Run the Monitor
./resp_guard

🔥 Simulating System Load (Demo)

Open another terminal and run:

yes > /dev/null


You will observe:

Increased scheduling delay

Repeated warnings:

WARNING: System responsiveness degraded!

🛑 Stopping the Programs

Stop resp_guard:

CTRL + C


Stop CPU stress:

CTRL + C

📊 Sample Output
Scheduling delay: 2030 microseconds
WARNING: System responsiveness degraded!
------------------------------------
Scheduling delay: 851 microseconds
WARNING: System responsiveness degraded!

🧪 Demonstration Flow (Recommended)

Run resp_guard

Observe normal behavior

Start yes > /dev/null

Observe warnings

Stop stress process

Show system recovery

Perfect for hackathon or viva demos ✅

⚠️ Limitations

Current implementation focuses on detection, not enforcement

Runs in user space (kernel hooks are discussed conceptually)

Thresholds are static and demo-oriented

WSL does not support custom kernel modules

🔮 Future Enhancements

Loadable Kernel Module (LKM) implementation

Per-process CPU throttling using cgroups

Priority adjustment via scheduler hooks

Logging and visualization support

Auto-recovery and adaptive thresholds

🏁 Conclusion

This project highlights how minimal OS-level observation can reveal serious responsiveness issues — and how careful control, not brute-force termination, is the right design philosophy for modern operating systems.
