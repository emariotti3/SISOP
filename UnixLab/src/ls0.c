#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>

void ls0() {
    //Prints the names of the files and directories
    //contained in the current directory.
    //Each file/directory is printed on a separate line.
    DIR *dir = opendir(".");
    if(!dir){
        return;
    }
    struct dirent *d;
    while((d = readdir(dir))){
        if (*(d->d_name) != '.'){
          printf("%s\n", d->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    ls0();
    return 0;
}
