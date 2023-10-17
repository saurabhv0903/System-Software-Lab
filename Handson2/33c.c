/*
============================================================================
Name : 33c.c
Author: Saurabh Varade
Description : Write a program to communicate between two machines using socket.
Date: 18 Oct 2023
============================================================================
*/


#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main() {

 	int cfd = socket(AF_INET, SOCK_STREAM, 0);
    	
	struct sockaddr_in server;
    	
	server.sin_family = AF_INET;
    	server.sin_port = htons(5000);
    	server.sin_addr.s_addr = inet_addr("127.0.0.1");

   	int connect_res = connect(cfd, (struct sockaddr*)&server, sizeof(server));
   	
	if(connect_res == -1) {
        	char connect_error[] = "Error connecting\n";
        	return -1;
    	}
    	
	printf("Connected to server\n");
    	
	char recv_buff[500];
    	char send_buff[500];
    	
	while(1) {
	
		printf("Enter message to server: ");
		scanf("%s", send_buff);
	
		send(cfd, &send_buff, sizeof(send_buff), 0);
		printf("Message received from server: ");
        
		recv(cfd, &recv_buff, sizeof(recv_buff), 0);
        	printf("%s\n", recv_buff);
    	
	}
	return 0;
}
