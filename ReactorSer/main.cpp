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
#include <arpa/inet.h>


#define SIZE 1
#define PORT 12345
#define IP_ADDR INADDR_ANY

int main() {
    int _fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == _fd)
    {
        printf("socket");
        exit(EXIT_FAILURE);
    }
	
	printf("socket create over \n");
    struct sockaddr_in local_addr;
    memset(&local_addr, 0, sizeof(struct sockaddr_in));

    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(PORT);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(_fd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));
    if (-1 == ret)
    {
        printf("bind");
        exit(EXIT_FAILURE);
    }
	printf("bind create over \n");


    unsigned int lisnum = 5;
    ret = listen(_fd, lisnum);
    if (-1 == ret)
    {
        printf("listen");
        exit(EXIT_FAILURE);
    }
	printf("listen create over \n");
    printf("Wait for client connection!\n");

    //4. accept the connection
    int new_fd;
    socklen_t len;
    struct sockaddr_in client_addr;
	
	std::string _buff;
	while(1){		
		new_fd = accept(_fd, (struct sockaddr *)&client_addr, &len);
		if (-1 == new_fd)
		{
			printf("accept");
			exit(EXIT_FAILURE);
		}
		printf("accept\n");
		printf("new_fd : %d\n",new_fd);
		while(1){		
			char _tmp_buff[SIZE+1];
			memset(_tmp_buff, 0, SIZE);
			int length = recv(new_fd, _tmp_buff, SIZE, 0); 	
			if(!length){
				break;				
			}
			printf("length %d\n",length);
			_tmp_buff[SIZE] = '\0';
			printf("_tmp_buff %s\n",_tmp_buff.c_str());
			_buff += _tmp_buff;
		}
						
		printf("final _buff %s\n",_buff.c_str());
	}


    std::cout << "ser rdy" << std::endl;
    return 0;
}