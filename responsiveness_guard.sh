

THRESHOLD=80
CPU_LIMIT=30

echo "System Responsiveness Guard Started..."

ps -eo pid,comm,%cpu --no-headers | while read pid cmd cpu; do
    cpu_int=${cpu%.*}

    if [ "$cpu_int" -gt "$THRESHOLD" ]; then
        echo "High CPU usage detected:"
        echo "Process: $cmd | PID: $pid | CPU: $cpu%"

        renice +10 -p $pid
        cpulimit -p $pid -l $CPU_LIMIT &

        echo "Applied priority reduction and CPU limit"
    fi
done

"cilck clt+o & Enter & clt+x"
##Make executable:##

chmod +x responsiveness_guard.sh

