#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


void touch0(const char *file) {
    //Receives the pathname for a file.
    //Creates a file with the specified name at the
    //specified location.
    int fd = open(file, O_WRONLY|O_CREAT|O_NOCTTY|O_NONBLOCK, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (fd < 0){
      return;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    touch0(argv[1]);
    return 0;
}
