#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{	
	if (!fork()) 
		execlp("gcc", "gcc", "test_hello.c", "-o", "hello", NULL);
	
	int status = 0;
	wait(&status);
	execlp("./hello", "./hello", NULL);
  
  return 0;
}
