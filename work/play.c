#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

#ifndef _PLAY_H_
#define _PLAY_H_
#include "play.h"
#endif

char *para[]={"echo","EXIT", "Success!", NULL};
int totalNum = 0, userWinNum = 0;
int pid, lock = 0, i;
int computerChoice;
int userChoice;

void stopPlay(int iSignNo, siginfo_t *pInfo, void *pReserved) { // log the pid to close
    if(totalNum!=0) {
        printf("\n总共进行了%d局，玩家的胜率是%.2f%%\n游戏结束！", totalNum, (float)userWinNum/(float)totalNum);
    }
    printf("\n等待进程 %d 退出~~~\n", getpid());
    if(execv("/bin/echo", para)==-1) {
        perror("execv");
        exit(1);
    }
    exit(0);
    return ;
}

void startPlay() {
    while((pid=fork())==-1);
    if (pid == 0) { // print the rule
        printf("石头剪刀布游戏\n");
        printf("规则如下：\n");
        printf("输入0代表石头，输入1代表剪刀，输入2代表布\n");
        printf("输入之后按下回车，与计算机的选择相比较\n");
        printf("输入之后按下回车，与计算机的选择相比较\n");
        printf("剪刀赢布，布赢石头，石头赢剪刀\n");
        printf("输入Ctrl+C退出游戏，之后会结算输赢局数，可选择是否保存为文件\n");
        while(lock==0);
        exit(0);
    }
    else { // play the game
        struct sigaction act; /*包含信号处理动作的结构体*/
        act.sa_sigaction=stopPlay;  /*指定信号处理函数*/
        act.sa_flags=SA_SIGINFO;   /*表明信号处理函数由sa_sigaction指定*/
        sigemptyset(&act.sa_mask);
        /*信号集处理函数，将act.sa_mask所指向的信号集清空，*/
        /*即不包含任何信号*/
        sigaction(SIGINT,&act,NULL);   /*注册SIGINT信号*/
        // 0 is Rock
        // 1 is Scissor
        // 2 is Paper
        while(scanf("%d", &userChoice)!=-1) {
            computerChoice = rand() % 3;
            totalNum++;
            printf("这是第%d局，用户的选择是%s，电脑的选择是%s\n这一局赢得是：",
                totalNum,
                userChoice == 0 ? "石头" : (userChoice == 1 ? "剪刀" : "布"),
                computerChoice == 0 ? "石头" : (computerChoice == 1 ? "剪刀" : "布")
            );
            int res = userChoice - computerChoice;
            if(res == -1 || res == 2) {
                userWinNum++;
                printf("用户！\n");
            }
            else if(res == 0) {
                printf("平局！\n");
            }
            else {
                printf("电脑！\n");
            }
        }
        lock = 1;
        exit(0);
    }
    return ;
}