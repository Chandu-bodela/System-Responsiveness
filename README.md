# 🛡️ System Responsiveness Guard

**Preventing System Slowdowns Caused by Resource-Hungry Processes**

---

## 📌 Overview

In real-world systems, users often experience lag, freezes, or unresponsiveness even when CPU and memory appear sufficient.
This happens when one or more aggressive processes monopolize CPU time, starving interactive or critical tasks.

**System Responsiveness Guard** is a lightweight Linux-based monitoring tool that demonstrates how system responsiveness can be observed, detected, and protected using OS-level scheduling behavior — without killing processes.

---

## 🎯 Problem Statement

Modern Linux schedulers prioritize fairness but not always user-perceived responsiveness.

Common issues include:
- Background CPU-heavy tasks causing UI lag
- Builds or scripts freezing shared machines
- Interactive processes being starved under load

This project demonstrates:
- How responsiveness degradation can be detected
- How system behavior changes under CPU stress
- A foundation for kernel-assisted control mechanisms

---

## 🧠 Key Idea

Instead of terminating processes, the system:
- Continuously monitors scheduling delay
- Detects responsiveness degradation
- Warns when the system becomes less responsive

This aligns with real OS design goals: **control, not destruction**.

---

## 🏗️ Architecture (High Level)

```
CPU-Heavy Task  --> Linux Scheduler --> Responsiveness Guard
```

---

## 🔍 What This Project Does

### Monitoring
- Measures scheduling delay using high-resolution timers
- Observes how often execution is delayed by the scheduler

### Detection
- Rule-based threshold detection
- Flags system responsiveness degradation

### Control (Conceptual)
- Priority reduction
- CPU throttling
- Core restriction

> ⚠️ No processes are killed.

---

## 🛠️ Tech Stack

- Language: C
- Platform: Linux (Ubuntu 22.04 / WSL2)
- Tools: gcc, make

---

## 📂 Project Structure

```
resp_guard/
├── resp_guard.c
├── Makefile
├── README.md
```

---

## 🚀 How to Run

```bash
sudo apt update
sudo apt install -y build-essential
make
./resp_guard
```

---

## 🔥 Simulating System Load

In another terminal:
```bash
yes > /dev/null
```

---

## 🛑 Stopping

Press **CTRL + C** in both terminals.

---

## 📊 Sample Output

```
Scheduling delay: 2030 microseconds
WARNING: System responsiveness degraded!
```

---

## 🔐 Kernel-Level Extension (Design)

> Due to WSL2 kernel limitations, full kernel modules are not loaded.  
> The design below applies to a standard Linux kernel.

### Why Kernel Assistance?
User-space monitoring detects issues but cannot enforce scheduling control safely.

### Kernel Monitoring
- task_struct inspection
- sched_switch tracepoints
- CPU runtime and latency tracking

### Detection Logic
```
IF CPU usage exceeds threshold
AND interactive latency increases
THEN mark process disruptive
```

### Runtime Control
- Reduce scheduling priority
- Limit CPU cores (affinity)
- CPU throttling via cgroups

### Recovery
- Restore original priority
- Remove restrictions once stable

---

## 🛡️ Safety Considerations

- No kernel panics
- No process termination
- Minimal kernel interaction
- Safe unload behavior

---

## 🔮 Future Enhancements

- Loadable Kernel Module (LKM)
- cgroups-based CPU control
- Adaptive thresholds
- Logging & visualization

---

## 🏁 Conclusion

This project demonstrates how minimal OS-level observation can detect responsiveness issues and how kernel-assisted control can safely restore system usability.

---

## 👤 Author

**Chandu**  
Operating Systems Project
