#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PORT 5001

// 保存消息
void save_record(char msg[], int type) {
    FILE *fp;
    int fd;
    // 打开文件，返回文件指针
    if( (fd = open("record.txt", O_RDWR)) == -1) {
        printf ("fail to open!\n");
        exit(1);         /*出错退出*/
    }
    // 在打开的文件上打开一个流，基于已存在的文件描述符打开流，并从文件尾开始读写
    if((fp = fdopen(fd, "a+")) == NULL) {
        printf ("fail to open stream!\n");
        exit(1);         /*出错退出*/
    }
    // 获取时间
    char showTime[30];
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (showTime,sizeof(showTime),"%Y/%m/%d %H:%M:%S",timeinfo);
    // 写入信息到文件中
    if(type == 1) {
        fprintf(fp, "%s -> Client: %s\n", showTime, msg);
    }
    else {
        fprintf(fp, "%s -> Server: %s\n", showTime, msg);
    }
    fclose(fp);
}

int main() {
    int sockfd;     // 客户套接字标识符
    int len;        // 客户消息长度
    struct sockaddr_in addr;     // 客户套接字地址
    int newsockfd;
    char buf[256] = "come on!";  //要发送的消息
    int len2;
    char rebuf[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);    // 创建套接字
    addr.sin_family = AF_INET;                   // 客户端套接字地址中的域
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);                 // 客户端套接字端口
    len = sizeof(addr);
    newsockfd = connect(sockfd, (struct sockaddr *) &addr, len);    //发送连接服务器的请求
    if (newsockfd == -1) {
        perror("连接失败");
        return 1;
    }
    len2 = sizeof(buf);
    int choose = 0;
    while(1) {
        printf("输入1开始与服务器对话\n");
        printf("输入2查看聊天记录\n");
        printf("输入0退出\n");
        scanf("%d", &choose);
        if(choose == 1) {
            while (1) {
                printf("请输入要发送的数据: ");
                scanf("%s", buf);
                if(strcmp(buf, "quit") ==0) {
                    break;
                }
                send(sockfd, buf, len2, 0);  // 发送消息
                save_record(buf, 1);   // 保存消息到本地
                // 接收消息
                if(recv(sockfd,rebuf,256,0)>0) {
                    printf("收到服务器消息: %s\n",rebuf);
                }
                save_record(rebuf, 2); // 保存消息到本地
            }
            close(sockfd); // 关闭连接
        }
        else if(choose == 2) {
            system("cat record.txt");
        }
        else {
            printf("程序结束！\n");
            break;
        }
    }
    return 0;
}
