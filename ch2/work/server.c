#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <linux/stat.h>

#define FIFO_FILE "/tmp/TEMPFIFO" /*命名管道的路径、文件名*/


// Create FIFO-FILE if not exists
void init(FILE *fp) {
    if ((fp = fopen(FIFO_FILE, "r")) == NULL) {/*如果命名管道文件不存在，要先创建一个*/
        umask(0);//清除文件创建时权限位的屏蔽作用
        mknod(FIFO_FILE, S_IFIFO | 0666, 0);//创建FIFO文件
        printf("Create new FIFO-FILE successed. \n");
    } else {
        fclose(fp);
    }
}


int main() {
    FILE *fp;
    char readbuf[80];

    init(fp);

    while (1) {
        if ((fp = fopen(FIFO_FILE, "r")) == NULL) {/*打开命名管道文件*/
            printf("open fifo failed. \n");
            exit(1);
        }

        if (fgets(readbuf, 80, fp) != NULL) {/*从命名管道文件中读数据*/
            printf("Received string :%s \n", readbuf);
            fclose(fp);
        } else {
            if (ferror(fp)) {
                printf("read fifo failed.\n");
                exit(1);
            }
        }
    }
    return 0;
}
