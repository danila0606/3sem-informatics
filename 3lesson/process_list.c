#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{
	int N = 0;
	scanf("%d", &N);

	printf("New process PID:[%d]\n", getpid());

	for(int i = 0; i < N; i++) {
		pid_t pid = fork();
		if (pid == -1) {
			printf("Error\n");
			exit(1);
		}
		else if (pid == 0)
			printf("New child process %d. PID:[%d], PPID:[%d]\n", i, getpid(), getppid());
		else {
			int status = 0;
			wait(&status);
			printf("Child process %d PID:[%d] finished.", i, pid);
            printf("Parent process PID:[%d]\n", getpid());
			exit(0);
		}
	}

	return 0;
}
