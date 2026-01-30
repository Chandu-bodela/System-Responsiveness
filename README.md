# 🛡️ System Responsiveness Guard

**Preventing System Slowdowns Caused by Resource-Hungry Processes**

---

## 📌 Overview

In real-world Linux systems, users often experience lag, freezes, or unresponsiveness even when CPU and memory appear sufficient.  
This usually occurs when one or more aggressive background processes monopolize CPU time, starving interactive or critical tasks.

**System Responsiveness Guard** is a lightweight, user-space monitoring tool that demonstrates how system responsiveness degradation can be **observed, detected, and reported** using OS-level scheduling behavior — without killing any processes.

---

## 🎯 Problem Statement

Modern Linux schedulers prioritize fairness, but they do not always guarantee **user-perceived responsiveness**.

Common issues include:
- CPU-heavy background jobs causing UI lag
- Build processes freezing shared systems
- Interactive tasks being delayed under load

This project demonstrates:
- How responsiveness degradation occurs
- How scheduling delays can be detected
- A foundation for safe system-level control mechanisms

---

## 🧠 Key Idea

Instead of terminating processes, the system:

- Continuously monitors scheduling delay
- Detects responsiveness degradation
- Warns the user when the system becomes less responsive

> **Control, not destruction** — aligned with real OS design principles.

---

## 🏗️ High-Level Architecture

CPU-Heavy Task --> Linux Scheduler --> Responsiveness Guard


---

## 🔍 What This Project Does

### Monitoring
- Uses high-resolution timers
- Measures scheduling latency

### Detection
- Threshold-based detection
- Flags responsiveness degradation

### Control (Conceptual)
- Priority reduction
- CPU throttling
- Core restriction

> ⚠️ No processes are killed in this implementation.

---

## 🛠️ Tech Stack

- **Language:** C  
- **Platform:** Linux (Ubuntu 22.04 / WSL2)  
- **Tools:** gcc, make  

---

## 📂 Project Structure

System-Responsiveness/
├── resp_guard/
│ ├── resp_guard.c
│ ├── Makefile
├── README.md
├── ALL_COMMANDS.md
├── docs/
│ └── System_Responsiveness_Guard_Report.pdf

---

## 🚀 How to Run

### 1️⃣ Install Dependencies
```bash
sudo apt update
sudo apt install -y build-essential
---



## **🛠️ Installation**

Update system packages and install required build tools:

```bash
sudo apt update
sudo apt install -y build-essential
---
## 🚀 Build and Run
# Build the Project
bash

cd resp_guard
make
-------------
# Run the Program
bash

./resp_guard

###🔥 Simulating CPU Load
Open another terminal and execute:

bash

yes > /dev/null
This command intentionally creates a CPU-hogging process to test system responsiveness under stress.

### 🛑 Stopping the Programs
Press CTRL + C in both terminals to stop execution.

📊 Sample Output
text
Copy code
Scheduling delay: 2030 microseconds
WARNING: System responsiveness degraded!
🔐 Kernel-Level Extension (Design Only)
Full kernel modules are not loaded due to WSL2 limitations.
The following design applies to a standard Linux kernel environment.

Kernel Monitoring
task_struct inspection

sched_switch tracepoints

CPU runtime and latency tracking

Detection Logic
IF CPU usage exceeds a defined threshold

AND interactive latency increases

THEN mark the process as disruptive

Runtime Control
Reduce scheduling priority

Apply CPU affinity

Throttle CPU using cgroups

Recovery Strategy
Restore original priority

Remove restrictions once system stabilizes

🛡️ Safety Considerations
No kernel panics

No forced process termination

Minimal system impact

Safe, non-intrusive monitoring

🔮 Future Enhancements
Loadable Kernel Module (LKM)

cgroups-based enforcement

Adaptive thresholds

Logging and visualization support

📚 References & Learning Resources
Linux Scheduling
CFS Scheduler Design
https://www.kernel.org/doc/html/latest/scheduler/sched-design-CFS.html

Scheduling Policies (sched, nice)
https://man7.org/linux/man-pages/man7/sched.7.html

Process Monitoring
top command
https://man7.org/linux/man-pages/man1/top.1.html

ps command
https://man7.org/linux/man-pages/man1/ps.1.html

nice
https://man7.org/linux/man-pages/man1/nice.1.html

renice
https://man7.org/linux/man-pages/man8/renice.8.html

CPU Stress Testing
yes command
https://man7.org/linux/man-pages/man1/yes.1.html

Related Work
System76 Scheduler (Pop!_OS)
https://github.com/pop-os/system76-scheduler

Kernel Concepts
task_struct
https://elixir.bootlin.com/linux/latest/source/include/linux/sched.h

Scheduler Tracepoints
https://www.kernel.org/doc/html/latest/trace/events-sched.html

Control Mechanisms
Control Groups (cgroups v2)
https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v2.html

🏁 Conclusion
This project illustrates how minimal OS-level observation can identify system responsiveness issues and how kernel-assisted mechanisms can safely restore usability without disrupting running processes.
EOF

markdown
Copy code
