#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF_SZ 4096

void cat0(const char *file) {
    //Receives a reference to a file.
    //Writes the contents of the file to standard output.
    //Pre-requisites: the file exists, it is regular.
    char *buffer[BUFF_SZ + 1];
    size_t count = 0;
    int fd = open(file, O_RDONLY|_FILE_OFFSET_BITS);
    if (fd == -1){
      return;
    }
    while ((count = read(fd, buffer, BUFF_SZ)) > 0) {
        count -= write(STDOUT_FILENO, buffer, count);
        while (count > 0){
            count -= write(STDOUT_FILENO, buffer, count);
        }
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    cat0(argv[1]);
    return 0;
}
