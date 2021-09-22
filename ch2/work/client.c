#include "semshm.h"

int main() {
    int shmid;
    int key = 1022;
    pid_t p;
    char c;
    char *shmptr, *s;
    int cnt;
    setvbuf(stdout, NULL, _IONBF, 0);

    shmid = open_shmid(shmid, key);
    shmptr = create_shmptr(shmptr, shmid);

    printf("This is the client, now you can send a message to the server, please enter the message and press Enter to send\n");

    if ((p = fork()) < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    while (1) {
        if (p == 0) {
            while (*shmptr != 's') {
                sleep(1);
            }
            printf("\n\033[43;37mReceive From Server:\33[0m ");
            cnt = 0;
            for (s = shmptr + 1; *s != '\0'; s++) {
                cnt++;
                putchar(*s);
            }
            printf("\nReceive Total %d letter", cnt);
            printf("\n>> ");
            *shmptr = '#';
        }
        else {
            printf(">> ");
            scanf("%[^\n]", shmptr + 1);
            getchar();
            *shmptr = 'c';
            while (*shmptr != '#') {
                sleep(1);
            }
            printf("\033[46;37mSuccessfully Sent\33[0m\n");
        }
    }
    return 0;
}