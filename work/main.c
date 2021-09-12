#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#ifndef _PLAY_H_
#define _PLAY_H_
#include "play.h"
#endif

int main() {
    // struct sigaction act; /*包含信号处理动作的结构体*/
    // act.sa_sigaction=stopPlay;  /*指定信号处理函数*/
    // act.sa_flags=SA_SIGINFO;   /*表明信号处理函数由sa_sigaction指定*/
    // sigemptyset(&act.sa_mask);
    // /*信号集处理函数，将act.sa_mask所指向的信号集清空，*/
    // /*即不包含任何信号*/
    // sigaction(SIGINT,&act,NULL);   /*注册SIGINT信号*/

    startPlay();
    
    return 0;
}