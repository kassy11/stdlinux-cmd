#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define BUFFER_SIZE 2048
#define  DEFAULT_FILENAME_LEN 20

static void do_cat(const char* path);
static void errormsg(const char* s);

int main(int argc, char* argv[]){
  int i;
  char filename[DEFAULT_FILENAME_LEN][256];

      for (i=0; i<argc; i++){
          strcpy(filename[i], argv[i]);
      }


  for(i=0; i<argc; i++){
    do_cat(filename[i]);
  }
}


static void do_cat(const char *path){
  int fd;
  unsigned char buf[BUFFER_SIZE];
  int n;

  fd = open(path, O_RDONLY);
  if(fd < 0){
    errormsg(path);
  }
  for(;;){
    n = read(fd, buf, sizeof buf );
    if(n<0) errormsg(path);
    if(n == 0) break;
    if(write(STDOUT_FILENO, buf, n) < 0) errormsg(path);
  }

  if(close(fd) < 0) errormsg(path);
}

void errormsg(const char *s){
  perror(s);
  exit(1);
}
