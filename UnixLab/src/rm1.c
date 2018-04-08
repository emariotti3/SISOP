#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//#define BUFF_SZ 100

void rm1(const char *file) {
    //Receives a reference to a file. If it is the only
    //remaining reference to the file, the file will be deleted.
    //If there are more references to the file, it will
    //only eliminate the received reference.
    //Pre-requisites: the file exists and it is regular.
    if (unlink(file) == -1){
      //char error_msg[BUFF_SZ] = {"rm: cannot remove "};
      //perror(strncat(error_msg, file, BUFF_SZ - strlen(error_msg)));
      printf ("rm: cannot remove '%s': %s\n",file, strerror(errno));
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    rm1(argv[1]);
    return 0;
}
