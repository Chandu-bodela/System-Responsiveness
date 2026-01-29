
# Commands Used – System Responsiveness Guard

step 1: Monitor system
top

Step 2: Create CPU-hogging process
yes > /dev/null

Step 3: Identify high CPU usage
ps -eo pid,comm,%cpu --sort=-%cpu | head -5

Step 4: Reduce priority manually
renice +10 -p <PID>

Step 5: Install cpulimit
sudo apt update
sudo apt install cpulimit

Step 6: Run responsiveness guard
sudo ./responsiveness_guard.sh

Step 7: Verify improvement
top

Step 8: Stop CPU hog
killall yes

Result

CPU usage controlled
System responsiveness restored
No process terminated
