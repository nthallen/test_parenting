#! /bin/bash
./parent_test.sh &
sleep 5
echo "Parent PID is $!"
ps | grep -e "$!\|PPID"
