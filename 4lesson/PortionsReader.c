#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main()
{
    int fd;
    size_t N;
    scanf("%u", &N);


    if ((fd = open("input.txt", O_RDONLY)) < 0) {
        printf("Can't open file\n");
        exit(-1);
    }

    char s[N];

    int i = 0;
    while ((i = read(fd, s, N)) != 0) {
        printf("[%s]\n", s);
    }

    close(fd);

    return 0;
}
