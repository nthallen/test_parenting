# test_parenting
## Test program to explore effects of exec on parent/child relationships under cygwin

## Fixed

**Note:** This problem has been fixed in version 3.1.2 of the cygwin package.

## Running

To run this test program:
- make parent_test
- ./parent_test2.sh

## What is going on:

`parent_test.sh` launches `sleep 15` in the background, reports the
parent and child PIDs and runs `ps` to show that the operating system
is in agreement. Then it executes `exec ./parent_test`, which replaces
the bash shell with the minimal test program to monitor the child
processes.

`parent_test2.sh` launches `parent_test.sh` in the background, reports
its PID, waits a bit to avoid confusion and then runs `ps` to show
the geneology after the exec call.

## How it should work:

On Ubuntu 16.04, I get the following:

```
Parent pid is 5031
Child pid is 5033
UID         PID   PPID  C STIME TTY          TIME CMD
nort       5031   5030  0 15:16 pts/19   00:00:00 /bin/bash ./parent_test.sh
nort       5033   5031  0 15:16 pts/19   00:00:00 sleep 15
nort       5034   5031  0 15:16 pts/19   00:00:00 ps -f
Parent PID is 5031
UID         PID   PPID  C STIME TTY          TIME CMD
nort       5031   5030  0 15:16 pts/19   00:00:00 ./parent_test
nort       5033   5031  0 15:16 pts/19   00:00:00 sleep 15
Process 5033 terminated: status 0000
No more children
```

As you can see, there are two reports from `ps`, followed by a report
from `parent_test` that the child precess (5033) has terminated.

## What happens under cygwin
```
$ uname -a
CYGWIN_NT-10.0 easwhlpt3425080 3.0.7(0.338/5/3) 2019-04-30 18:08 x86_64 Cygwin
$ ./parent_test2.sh
Parent pid is 2386
Child pid is 2388
     UID     PID    PPID  TTY        STIME COMMAND
    nort    2389    2386 pty2     15:17:29 /usr/bin/ps
    nort    2390    2386 pty2     15:17:30 /usr/bin/bash
    nort    2388    2386 pty2     15:17:29 /usr/bin/sleep
    nort    2386    2385 pty2     15:17:29 /usr/bin/bash
No more children
Parent PID is 2386
     UID     PID    PPID  TTY        STIME COMMAND
    nort    2388    2386 pty2     15:17:29 /usr/bin/sleep
    nort    2386    2385 pty2     15:17:29 /home/nort/SW/test/parenting/parent_test
```

Here you can see that `parent_test` immediately reports "no more children"
even though the subsequent `ps` output still shows the expected parent/child
relationship. (Note that parent_test.c includes a delay after "No more children"
before terminating, allowing it to stay around long enough to be observed.)
