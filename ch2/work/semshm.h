#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


// 创建共享缓存区
int create_shmid(int shmid, int key) {
    if ((shmid = shmget(key, 1024, 0666 | IPC_CREAT)) < 0) {
        printf("Shmget failed\n");
        exit(1);
    }
    return shmid;
}


// 打开共享缓存区
int open_shmid(int shmid, int key){
    if ((shmid = shmget(key, 1024, 0666)) < 0) {
        printf("Shmget failed\n");
        exit(1);
    }
    return shmid;
}


//
char * create_shmptr(char * shmptr, int shmid) {
    if ((shmptr = shmat(shmid, 0, 0)) == (char *) -1) {
        shmctl(shmid, IPC_RMID, (struct shmid_ds *) shmptr);
        printf("Shmat error\n");
        exit(2);
    }
    return shmptr;
}