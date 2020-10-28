#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define SIZE 100

struct ThreadData
{
    char* fifo_name;
};

void *Read(void* data)
{
    struct ThreadData* info = (struct ThreadData*)data;
    int fd;

    if ((fd = open(info->fifo_name, O_RDONLY)) < 0) {
        printf("Can't open FIFO for reading\n");
        exit(-1);
    }

    char word[SIZE];

    while(1) {
        int size = read(fd, word, SIZE);
        printf("%s\n", word);
    }
}
void *Write(void* data)
{
    struct ThreadData* info = (struct ThreadData*)data;
    int fd;
    if ((fd = open(info->fifo_name, O_WRONLY)) < 0) {
        printf("Can't open FIFO for writting\n");
        exit(-1);
    }

    char word[SIZE];

    while(1) {
        fgets(word, SIZE, stdin);
        write(fd, word, SIZE);
    }
}

int main(int argc, char* argv[]) {

    (void)umask(0);

    int f1 = mknod("aaaa.fifo", S_IFIFO | 0666, 0);

    if (f1 < 0 && errno != EEXIST) {
        printf("Cant create aaaa FIFO\n");
        exit(-1);
    }

    int f2 = mknod("bbbb.fifo", S_IFIFO | 0666, 0);

    if (f2 < 0 && errno != EEXIST) {
        printf("Cant create bbbb FIFO\n");
        exit(-1);
    }

    int id = atoi(argv[1]);
    struct ThreadData Th_read, Th_write;

    char read_[1], write_[1];

    if (!id) {
        read_[0] = '1';
        write_[0] = '0';
    }
    else {
        read_[0] = '0';
        write_[0] = '1';
    }

    pthread_t read_id, write_id;

    Th_read.fifo_name = read_;
    Th_write.fifo_name = write_;

    pthread_create(&read_id, NULL, Read, &Th_read);
    pthread_create(&write_id, NULL, Write, &Th_write);

    return 0;
}
