#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <unistd.h>

#define FILE_PATH 1
#define LINK_PATH 2

void ln1(const char *file, const char *dst) {
    //Receives an origin path for a regular file.
    //Creates a hard link for origin path 'file' with the
    //name indicated by 'dst'.
    //Pre-requisites: 'file' points to an existing
    //regular file.
    link(file, dst);
}

int main(int argc, char *argv[]) {
    if (argc <= 2){
        return -1;
    }
    ln1(argv[FILE_PATH], argv[LINK_PATH]);
    return 0;
}
