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

#define BUFF_SZ 20

void ps0() {
    //Lists the name of each currently running process
    //and its PID.
    int fd = 0;
    struct dirent *d;
    char buff[BUFF_SZ], path[PATH_MAX];
    DIR *dir = opendir("/proc");
    if(!dir){
        return;
    }
    while((d = readdir(dir))) {
        if (isdigit(*(d->d_name))) {
          memset(path, 0, strlen(path));
          memset(buff, '\0', PATH_MAX);
          strcat(path,"/proc/");
          strcat(path, d->d_name);
          strcat(path, "/comm");
          fd = open(path, O_RDONLY);
          if (fd == -1){
              continue;
          }
          read(fd, buff, PATH_MAX);
          printf("%s %s\n", d->d_name, buff);
          close(fd);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    ps0();
    return 0;
}
