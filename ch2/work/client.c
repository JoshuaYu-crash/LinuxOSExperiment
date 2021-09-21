#include <stdio.h>
#include <stdlib.h>
#define FIFO_FILE "/tmp/TEMPFIFO"/*命名管道的路径、文件名*/
#define MAX_LEN 1024


int main() {
    FILE *fp;
    int i;

    if ((fp = fopen(FIFO_FILE, "w")) == NULL) {/*打开命名管道文件*/
        printf("open fifo failed. \n");
        exit(1);
    }

    while(1) {
        printf("write : ");
        char read_str[MAX_LEN];
        scanf("%d", read_str);
        if (fputs(read_str, fp) == EOF) {
            printf("write fifo error. \n");
            exit(1);
        }
    }

    fclose(fp);
    return 0;

}

