#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORIGIN_PATH 1
#define DESTINY_PATH 2
#define BUFF_SZ 4096

void cp1(const char *file, const char *dst) {
    char *addr;
    struct stat file_info;
    int fd_origin = 0, fd_dst = 0, stat = 0;
    size_t buff_sz = 0;
    unsigned int written = 0;

    fd_origin = open(file, O_RDONLY);
    if (fd_origin == -1){
        return;
    }
    fd_dst = open(dst, O_WRONLY|O_CREAT|O_TRUNC);
    if (fd_dst == -1){
        close(fd_origin);
        return;
    }
    stat = fstat(fd_origin, &file_info);
    while ((stat!=-1) && (written < file_info.st_size)){
        buff_sz = (sysconf(_SC_PAGESIZE) > (file_info.st_size - written))? (file_info.st_size - written) : sysconf(_SC_PAGESIZE);
        addr = mmap(NULL, sysconf(_SC_PAGESIZE), PROT_READ, MAP_SHARED, fd_origin, written);
        if (addr == MAP_FAILED){
            break;
        }
        written += write(fd_dst, addr, buff_sz);

        if(munmap(addr, sysconf(_SC_PAGESIZE)) == -1) {
            break;
        }
    }
    close(fd_origin);
    close(fd_dst);
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    cp1(argv[ORIGIN_PATH], argv[DESTINY_PATH]);
    return 0;
}
