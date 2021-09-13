#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

void startPlay();
void stopPlay(int iSignNo, siginfo_t *pInfo, void *pReserved);