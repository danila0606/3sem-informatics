#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STOP 255
#define SIZE 100

struct mymsgbuf
{
    long type_;
    int nums_[SIZE];
}

int main()
{
    int msqid, len, maxlen;
    key_t  key;

    struct mymsgbuf mybuf;

    char pathname[]="a.c";
    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    while (1) {

        maxlen = SIZE;

        if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.type_ == STOP) {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
            exit(0);
        }

        printf("type_ = %ld, info = \n", mybuf.type_);
        for (int i = 0; i < SIZE; i++)
            printf("%d ", mybuf.nums_[i]);
    }

    return 0;
}
