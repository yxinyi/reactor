#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <errno.h>

void send(const char* ip_, int port_){	
    //1. create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sockfd)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
	printf("socket create over \n");

    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(struct sockaddr_in));
    
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port_);
    dest_addr.sin_addr.s_addr = inet_addr(ip_);
	
	int ret = connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	
    if(-1 == ret)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    printf("Connect the server(IP:%s) fd(%d) successed!\n", ip_,sockfd);
	
	char* buf = "hello world";
	
	int len = send(sockfd, buf, strlen(buf), 0);
	
}

int main(int argc, char *argv[]) {
	
	if(argc != 3){
		printf("input  ip port \n");
		return 0;
	}
	printf("argc %d \n",argc);
	const char* _target_ip = argv[1];
	int port = atoi(argv[2]);
	
	send(_target_ip,port);		
		
    return 0;
}