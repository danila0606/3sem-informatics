#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXWORD 100

int main(int argc, char *argv[]) {
	
	int fd1, fd2, result;
	size_t size;
	char str[MAXWORD];
	char name1[] = "aaa.fifo";
	char name2[] = "bbb.fifo";
	
	(void)umask(0);
	
	/*if (mknod(name2, S_IFIFO | 0666, 0) < 0) {
		printf("Cant\'t create FIFO\n");
		exit(-1);
	}*/

	if (argc < 2) {
		printf("prog needs arg\n");
		exit(-1);
	}
	
	if (atoi(argv[1]) == 1) {
		
		if ((fd1 = open(name1, O_WRONLY)) < 0) {
			printf("Can\'t open FIFO for writing\n");
			exit(-1);
		}
		if ((fd2 = open(name2, O_RDONLY)) < 0) {
			printf("Can\'t open FIFO for reading\n");
			exit(-1);
		}
		
		while (1) {
			pid_t pid = fork();
			
			if (pid == 0) {
				read(fd2, str, MAXWORD);
				printf("%s", str);
			}
			else {
				fgets(str, MAXWORD, stdin);
				write(fd1, str, strlen(str) + 1);
			}
			
		}
		
	}
	else if (atoi(argv[1]) == 2) {
		if ((fd1 = open(name1, O_RDONLY)) < 0) {
			printf("Can\'t open FIFO for reading\n");
			exit(-1);
		}
		if ((fd2 = open(name2, O_WRONLY)) < 0) {
			printf("Can\'t open FIFO for writing\n");
			exit(-1);
		}
		while(1) {
			pid_t pid = fork();
			if (pid == 0) {
				read(fd1, str, MAXWORD);
				printf("%s", str);
			}
			else {
				fgets(str, MAXWORD, stdin);
				write(fd2, str, strlen(str) + 1);
			}
			
		}
		
		
	}





return 0;
}
