#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i;
    for(i=1; i<argc; i++){
        FILE *f;
        int c;
        // ストリーム読み込み
        f = fopen(argv[i], "r");
        if(!f){
            perror(argv[i]);
            exit(1);
        }
        // cはバイト列
        while ((c = fgetc(f)) != EOF){
            if(putchar(c)<0) exit(1);
        }
        fclose(f);
    }
    exit(0);
}