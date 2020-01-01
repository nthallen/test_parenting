#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  for (;;) {
    int status;
    pid_t pid = waitpid(-1, &status, 0);
    switch (pid) {
      case 0:
        printf("Still have children: none have died\n");
        break;
      case -1:
        switch (errno) {
          case ECHILD:
            printf("No more children\n");
            sleep(10);
            return 0;
          case EINTR:
            printf("Received signal during waitpid()\n");
          default:
            printf("Unexpected error %d from waitpid(): %s\n",
              errno, strerror(errno));
            break;
        }
        break;
      default:
        printf("Process %d terminated: status %04X\n", pid, status);
        break;
    }
  }
  return 0;
}
