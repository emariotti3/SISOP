#define _POSIX_C_SOURCE 200809L

#include <unistd.h>

#define FILE_PATH 1
#define LINK_PATH 2

void ln0(const char *file, const char* link) {
    //Receives an origin path for a file or directory.
    //Creates a soft link for origin path 'file' with the
    //name indicated by 'link'.
    //Pre-requisites: 'file' points to an existing
    //file or directory.
    symlink(file, link);
}

int main(int argc, char *argv[]) {
    if (argc <= 2){
        return -1;
    }
    ln0(argv[FILE_PATH], argv[LINK_PATH]);
    return 0;
}
