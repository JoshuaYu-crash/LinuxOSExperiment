#include <stdio.h>
#include <stdlib.h>
#define FIFO_FILE "/tmp/TEMPFIFO"/*命名管道的路径、文件名*/
#define MAX_LEN 1024

FILE * openfile(FILE *fp, char type[]) {
    if ((fp = fopen(FIFO_FILE, type)) == NULL) {/*打开命名管道文件*/
        printf("open fifo failed. \n");
        exit(1);
    }
}

int main() {
    FILE *fp;
    int i, pid;
    while((pid=fork())==-1);
    // receive msg
    if(pid == 0) {
        while (1) {
            char readbuf[MAX_LEN];
            fp = openfile(fp, "r")
            if (fgets(readbuf, MAX_LEN, fp) != NULL) {/*从命名管道文件中读数据*/
                printf("Received message from Server :%s \n", readbuf);
                fclose(fp);
            }
            else {
                if (ferror(fp)) {
                    printf("read fifo failed.\n");
                    exit(1);
                }
            }
        }
    }
    // send msg
    else {
        while(1) {
            fp = openfile(fp, "w");
            printf("Wait for you send\n>> ");
            char read_str[MAX_LEN];
            scanf("%s", read_str);
            if (fputs(read_str, fp) == EOF) {
                printf("write fifo error. \n");
                exit(1);
            }
            fclose(fp);
        }
    }
    return 0;

}

