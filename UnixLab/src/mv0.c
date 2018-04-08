#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define ORIGIN_PATH 1
#define DEST_PATH 2

void mv0(const char *file, char *dst) {
    //Receives an origin path to a file or directory 'file'.
    //Receives a destiny path to a directory 'dst'.
    //Renames the link pointing to 'file' so that it will
    //its contents will now be accessible at 'dst'.
    //Pre-requisites: The destiny path 'dst' does not point
    //to an existing file.
    int success = rename(file, dst);
    if (success == -1){
        perror(strncat("mv0:", file, strlen(file)));
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 2){
        return -1;
    }
    mv0(argv[ORIGIN_PATH], argv[DEST_PATH]);
    return 0;
}
