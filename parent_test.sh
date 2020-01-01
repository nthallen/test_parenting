#! /bin/bash
echo Parent pid is $$
sleep 15 &
echo Child pid is $!
ps -f | grep -e "$$\|PPID" | grep -v grep
exec ./parent_test
