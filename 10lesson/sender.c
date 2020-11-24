#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define MAX_SIZE 1000

int len = 0;
char in[MAX_SIZE], out[MAX_SIZE];

int pos1 = 0, pos2 = 0;
int child_pid;

void set0(int signal)
{
    out[pos2 / 8] &= 255 - (1 << (pos2 % 8));
    pos2++;
    if (pos2 >= len * 8) {
        printf("%s\n", out);
    	  exit(0);
    }
    
    kill(child_pid, SIGCHLD);
}

void set1(int signal)
{
    out[pos2 / 8] |= 1 << (pos2 % 8);
    pos2++;
    if (pos2 >= len * 8) {
        printf("%s\n", out);
      	exit(0);
    }
        
    kill(child_pid, SIGCHLD);
}

void send_next(int signal)
{
    if ((in[pos1 / 8] & (1 << (pos1 % 8))) >> (pos1 % 8))
        kill(getppid(), SIGUSR2);
    else
        kill(getppid(), SIGUSR1);
        
    pos1++;
}

int main() {

    signal(SIGUSR1, set0);
    signal(SIGUSR2, set1);
    signal(SIGCHLD, send_next);
   
    scanf("%s", in);
    len = strlen(in);
    
    if (len > MAX_SIZE) {
    	printf("Len of Message > %d\n", MAX_SIZE);
    	exit(0);
    }
        
    printf("\n");
    int pid = fork();

    if (pid == 0) 
        while(1);
    else {
        child_pid = pid;
        kill(child_pid, SIGCHLD);
        while(1);
    }

    return 0;
}
