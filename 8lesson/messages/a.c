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
};

struct a{};

int main(void)
{

    int msqid, i, len;
    key_t  key;
    struct mymsgbuf mybuf;

    char pathname[]="a.c";
    key = ftok(pathname, 0);

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    for (i = 1; i <= 5; i++){

        mybuf.type_ = 1;
        int data[] = {1, 2, 3, 4, 5};
        memcpy(mybuf.nums_, data, sizeof(data));
        len = sizeof(data);

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
    
    mybuf.mtype = STOP;
    len         = 0;

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    return 0;
}
