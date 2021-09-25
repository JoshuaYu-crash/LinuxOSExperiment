#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5001

int main() {
    char sendbuf[256];
    char buf[256];
    int s_fd, c_fd;                // 服务器和客户套接字标识符
    int s_len, c_len;              // 服务器和客户消息长度
    struct sockaddr_in s_addr;     // 服务器套接字地址
    struct sockaddr_in c_addr;     // 客户套接字地址
    s_fd = socket(AF_INET, SOCK_STREAM, 0); // 创建套接字
    s_addr.sin_family = AF_INET;   // 定义服务器套接字地址中的地址域为IPv4
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 定义套接字地址
    s_addr.sin_port = htons(PORT); // 定义服务器套接字端口
    s_len = sizeof(s_addr);
    bind(s_fd, (struct sockaddr *) &s_addr, s_len);    // 绑定套接字与设置的端口号
    listen(s_fd, 10); //监听，最大连接请求设为10
    printf("请稍候，等待客户端发送数据\n");
    c_len = sizeof(c_addr); //接收客户端连接请求
    c_fd = accept(s_fd, (struct sockaddr *) &c_addr, (socklen_t *__restrict) &c_len);
    while (1) {
        if (recv(c_fd, buf, 256, 0) > 0) //接收消息recv(c_fd,buf,256,0)>0
        {
            printf("\033[46;37m收到客户端消息: %s\33[0m\n", buf);//输出到终端
            printf("请输入返回客户端的消息: ");
            scanf("%s", sendbuf);
            send(c_fd, sendbuf, sizeof(sendbuf), 0);//回复消息
        }
    }
    close(c_fd); // 关闭连接
}
