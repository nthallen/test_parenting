#! /bin/bash
echo Parent pid is $$
sleep 15 &
echo Child pid is $!
ps | grep -e "$$\|PPID"
exec ./parent_test
