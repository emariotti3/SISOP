#define _POSIX_C_SOURCE 200809L

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define ORIGIN_PATH 1
#define DESTINY_PATH 2
#define BUFF_SZ 4096

void cp0(const char *file, const char *dst) {
  //Receives the path to an origin file 'file'.
  //Receives the path to a destiny file 'dst'.
  //Writes the contents of 'file' to the file 'dst'.
  //Pre-requisites: the origin file exists, it is regular.
  //The written-to file 'dst' DOES NOT exist.
  size_t count = 0;
  int fd_origin = open(file, O_RDONLY);
  if (fd_origin == -1){
    return;
  }
  int fd_dst = open(dst, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  if (fd_dst == -1){
    close(fd_origin);
    return;
  }
  char buffer[BUFF_SZ + 1];
  while ((count = read(fd_origin, buffer, BUFF_SZ)) > 0) {
      count -= write(fd_dst, buffer, count);
      while (count > 0){
          count -= write(fd_dst, buffer, count);
      }
  }
  close(fd_origin);
  close(fd_dst);
}

int main(int argc, char *argv[]) {
    if (argc <= 1){
        return -1;
    }
    cp0(argv[ORIGIN_PATH], argv[DESTINY_PATH]);
    return 0;
}
