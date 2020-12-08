#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char* argv[]) {

    struct sockaddr_in addr, addr_to;
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &addr.sin_addr);
    bzero(addr.sin_zero, 8);
    
    int my_socket;
    if ((my_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Unable to create socket\n");
        exit(-1);
    }

    if (bind(my_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind\n");
        exit(-1);
    }

    for (int i = 0; i < 10; i++) {
        char mes[100];
        socklen_t addr_size;
        recvfrom(my_socket, mes, 100, 0, (struct sockaddr*)&addr_to, &addr_size);
        printf("Got message from %s:%hu: %s", inet_ntoa(addr_to.sin_addr), ntohs(addr_to.sin_port), mes);
    }
    printf("Sender exiting\n");
    return 0;
}
