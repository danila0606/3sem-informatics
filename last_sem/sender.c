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
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = INADDR_ANY;
    
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
    
    addr_to = addr;
    addr_to.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &addr_to.sin_addr);
    
    for (int i = 0; i < 5; i++) {
        char mes[100];
        fgets(mes,100, stdin);
        sendto(my_socket, mes, sizeof(mes), 0, (struct sockaddr*)&addr_to, sizeof(addr_to));
        printf("Message sended\n");
    }
    return 0;
}
