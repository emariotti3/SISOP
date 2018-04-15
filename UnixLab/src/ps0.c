#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>

#define BUFF_SZ 100

void ps0() {
    //Lists the name of each currently running process
    //and its PID.
    int fdcomm = 0, fdstat = 0;
    struct dirent *d;
    int pid;
    char buffcomm[BUFF_SZ], buffstat[BUFF_SZ], pathcomm[PATH_MAX], pathstat[PATH_MAX], name[BUFF_SZ], state;
    DIR *dir = opendir("/proc");
    if(!dir){
        return;
    }
    while((d = readdir(dir))) {
        if (isdigit(*(d->d_name))) {
          snprintf(pathcomm, PATH_MAX, "/proc/%s/comm", d->d_name);
          snprintf(pathstat, PATH_MAX, "/proc/%s/stat", d->d_name);
          fdcomm = open(pathcomm, O_RDONLY);
          if (fdcomm == -1){
              continue;
          }
          read(fdcomm, buffcomm, 10);
          fdstat = open(pathstat, O_RDONLY);
          if (fdstat == -1){
              close(fdcomm);
              continue;
          }
          read(fdstat, buffstat, BUFF_SZ);
          sscanf(buffstat, "%d %s %c",&pid, name, &state);
          printf("%d %s %s %c\n",pid, buffcomm, name, state);
          close(fdcomm);
          close(fdstat);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    ps0();
    return 0;
}
