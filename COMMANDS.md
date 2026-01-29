
# System Responsiveness Guard

step 1: Monitor system


Step 2: Create CPU-hogging process

Step 3: Identify high CPU usage

Step 4: Reduce priority manually


Step 5: Install cpulimit


Step 6: Run responsiveness guard


Step 7: Verify improvement


Step 8: Stop CPU hog


# Complete Command Execution Log


# Check initial system status
top

# Create CPU-hogging process
yes > /dev/null

# Identify high CPU usage process
ps -eo pid,comm,%cpu --sort=-%cpu | head -5

# Observe CPU impact
top

# Reduce priority of CPU-hogging process
renice +10 -p 616

# Update system and install cpulimit
sudo apt update
sudo apt install cpulimit

# Apply CPU limit manually
sudo cpulimit -p 616 -l 30

# Verify CPU usage reduction
top

# Make responsiveness guard script executable
chmod +x responsiveness_guard.sh

# Run automated system responsiveness guard
sudo ./responsiveness_guard.sh

# Final verification
top

# Stop CPU-hogging process
killall yes


## Result

CPU usage controlled

System responsiveness restored

No process terminated
