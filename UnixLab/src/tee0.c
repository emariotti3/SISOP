#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#define BUFF_SZ  4096
#define FD_SZ  2

void tee0(const char *file) {
    //Receives a path to a file at 'file'.
    //Reads input from standard input and writes it to
    //standard output and to the received file.
    //If 'file' does not exist it will be created.
    //If 'file' exists, its contents will be truncated.
    //Pre-requisites: If the file exists it is a regular file.
    int fd_out = open(file, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (fd_out == -1){
        return;
    }
    size_t rd_count = 0;
    char buffer[BUFF_SZ];
    int fds[] = {STDOUT_FILENO, fd_out};
    while((rd_count = read(STDIN_FILENO, buffer, BUFF_SZ)) > 0){
        for (size_t i = 0; i < FD_SZ; ++i){
            int wr_count = rd_count;
            while(wr_count > 0) {
                wr_count -= write(fds[i], buffer, wr_count);
            }
        }
    }
    close(fd_out);
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    tee0(argv[1]);
    return 0;
}
