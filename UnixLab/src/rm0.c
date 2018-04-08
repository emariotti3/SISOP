#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <unistd.h>


void rm0(const char *file) {
    //Receives a reference to a file. If it is the only
    //remaining reference to the file, the file will be deleted.
    //If there are more references to the file, it will
    //only eliminate the received reference.
    //Pre-requisites: the file exists and it is regular.
    unlink(file);
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    rm0(argv[1]);
    return 0;
}
