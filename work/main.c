#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#ifndef _PLAY_H_
#define _PLAY_H_
#include "play.h"
#endif

int main() {
    // struct sigaction act; /*�����źŴ������Ľṹ��*/
    // act.sa_sigaction=stopPlay;  /*ָ���źŴ�����*/
    // act.sa_flags=SA_SIGINFO;   /*�����źŴ�������sa_sigactionָ��*/
    // sigemptyset(&act.sa_mask);
    // /*�źż�����������act.sa_mask��ָ����źż���գ�*/
    // /*���������κ��ź�*/
    // sigaction(SIGINT,&act,NULL);   /*ע��SIGINT�ź�*/

    startPlay();
    
    return 0;
}