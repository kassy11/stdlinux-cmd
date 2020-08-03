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

  if(argc==1){
      char input[20];
      char *ptr;
      scanf("%s", input);
      ptr = strtok(input, " ");
      do_cat(ptr);
  }else{
      for(i=1; i<argc; i++){
          do_cat(argv[i]);
      }
  }
  exit(0);
}


static void do_cat(const char *path){
  int fd;
  unsigned char buf[BUFFER_SIZE];
  int n;

  // 読み込み専用でopenする
  fd = open(path, O_RDONLY);
  if(fd < 0)errormsg(path);

  for(;;){
      // ストリームfdからbufにバイト列をsizeof bufだけ読み込む
    n = read(fd, buf, sizeof buf );
    if(n<0) errormsg(path);
    // read()は全て読み込んだ時0を返す
    if(n == 0) break;
    //
    if(write(STDOUT_FILENO, buf, n) < 0) errormsg(path);
  }

  if(close(fd) < 0) errormsg(path);
}

void errormsg(const char *s){
    // perrorはerrnoに合ったエラー分を出力する
  perror(s);
  exit(1);
}
