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
        printf("\n�ܹ�������%d�֣���ҵ�ʤ����%.2f%%\n��Ϸ������", totalNum, (float)userWinNum/(float)totalNum);
    }
    printf("\n�ȴ����� %d �˳�~~~\n", getpid());
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
        printf("ʯͷ��������Ϸ\n");
        printf("�������£�\n");
        printf("����0����ʯͷ������1�������������2����\n");
        printf("����֮���»س�����������ѡ����Ƚ�\n");
        printf("����֮���»س�����������ѡ����Ƚ�\n");
        printf("����Ӯ������Ӯʯͷ��ʯͷӮ����\n");
        printf("����Ctrl+C�˳���Ϸ��֮��������Ӯ��������ѡ���Ƿ񱣴�Ϊ�ļ�\n");
        while(lock==0);
        exit(0);
    }
    else { // play the game
        struct sigaction act; /*�����źŴ������Ľṹ��*/
        act.sa_sigaction=stopPlay;  /*ָ���źŴ�����*/
        act.sa_flags=SA_SIGINFO;   /*�����źŴ�������sa_sigactionָ��*/
        sigemptyset(&act.sa_mask);
        /*�źż�����������act.sa_mask��ָ����źż���գ�*/
        /*���������κ��ź�*/
        sigaction(SIGINT,&act,NULL);   /*ע��SIGINT�ź�*/
        // 0 is Rock
        // 1 is Scissor
        // 2 is Paper
        while(scanf("%d", &userChoice)!=-1) {
            computerChoice = rand() % 3;
            totalNum++;
            printf("���ǵ�%d�֣��û���ѡ����%s�����Ե�ѡ����%s\n��һ��Ӯ���ǣ�",
                totalNum,
                userChoice == 0 ? "ʯͷ" : (userChoice == 1 ? "����" : "��"),
                computerChoice == 0 ? "ʯͷ" : (computerChoice == 1 ? "����" : "��")
            );
            int res = userChoice - computerChoice;
            if(res == -1 || res == 2) {
                userWinNum++;
                printf("�û���\n");
            }
            else if(res == 0) {
                printf("ƽ�֣�\n");
            }
            else {
                printf("���ԣ�\n");
            }
        }
        lock = 1;
        exit(0);
    }
    return ;
}