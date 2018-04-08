#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void stat0(const char *file) {
    //Receives a pathname to a file.
    //Prints file metadata: size (Bytes), name and type.
    //Pre-requisites: The path to the file must exist. The file must
    //either be a regular file or a directory.
    struct stat file_info;

    if (stat(file, &file_info) != -1){
      printf("Size: %lu \n", (unsigned long)file_info.st_size);
      printf("File: %s\n", file);
      printf("Type: ");
      if (S_ISREG(file_info.st_mode)){
          printf("regular file\n");
      }else{
          printf("directory\n");
      }
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    stat0(argv[1]);
    return 0;
}
