#! /bin/bash
./parent_test.sh &
sleep 2
echo "Parent PID is $!"
ps -f | grep -e "$!\|PPID" | grep -v grep
wait
