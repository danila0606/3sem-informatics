#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    int int_size = sizeof(int);
    
    if (pipe(fd) < 0) {
        printf("Pipe can't open\n");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork didn't work\n");
        exit(-1);
    }
    
    if (!pid) {

        int nums[2];

        if (read(fd[0], nums, int_size  * 2) != int_size  * 2) {
            printf("Bad pipe (can't read)\n");
            exit(-1);
        }
        
        int mult = nums[0] * nums[1];

        if (write(fd[1], &mult, int_size) != int_size) {
            printf("Bad pipe (can't write)\n");
            exit(-1);
        }
        
        exit(0);
    }
    else {
        int _nums[2];
        scanf("%d %d", &_nums[0], &_nums[1]);

        if (write(fd[1], _nums, int_size * 2) != int_size * 2) {
            printf("Bad pipe (can't write)\n");
            exit(-1);
        }

        int ans, status;
        wait(&status);

        if (read(fd[0], &ans, int_size) != int_size) {
            printf("Bad pipe (can't read)\n");
            exit(-1);
        }

        printf("%d\n", ans);
    }
    
    return 0;
}
