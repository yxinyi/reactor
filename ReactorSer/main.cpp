#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>


int main() {
    int _fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (-1 == _fd)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(struct sockaddr_in));

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(PORT);
    local_addr.sin_addr.s_addr = inet_addr(IP_ADDR);

    int ret = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));
    if (-1 == ret)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }


    unsigned int lisnum = 5;
    ret = listen(sockfd, lisnum);
    if (-1 == ret)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Wait for client connection!\n");

    //4. accept the connection
    int new_fd;
    socklen_t len;
    struct sockaddr_in client_addr;

    new_fd = accept(sockfd, (struct sockaddr *)&client_addr, &len);
    if (-1 == new_fd)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    else
    {
        //        printf("Server got connection: \n\tAddress:%s\tPort:%d\tSocket=%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), new_fd);
    }

    std::cout << "ser rdy" << std::endl;
    return 0;
}