/*
============================================================================
Name : 33s.c
Author : Saurabh Varade
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
#include <stdio.h>
#include <string.h>

int main() {
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
    	
	struct sockaddr_in server;
    	server.sin_family = AF_INET;
    	server.sin_port = htons(5000);
    	server.sin_addr.s_addr = inet_addr("127.0.0.1");
    	
	int bind_res = bind(sfd, (struct sockaddr*)&server, sizeof(server));

    	if(bind_res == -1) {
        	printf("Error binding\n");
        	return -1;
    	}
    	
	printf("Listening\n");
    	int listen_res = listen(sfd, 5);

    	if(listen_res != 0) {
        	printf("Error listening\n");
    	}

    	struct sockaddr_in client;
    	
	int client_size = sizeof(client);
   	int cfd = accept(sfd, (struct sockaddr*)&client, &client_size);
    	
	if(cfd == -1) {
        	printf("Error accepting client\n");
    	}
	
	printf("Client connected\n");
	
	char recv_buff[500];
	char send_buff[500];
    	
	while(1) {
    		recv(cfd, &recv_buff, sizeof(recv_buff), 0);
    		printf("Message received from client: %s\n", recv_buff);
    		printf("Enter message to send to client: ");
    		scanf("%s", send_buff);
    		send(cfd, &send_buff, sizeof(send_buff), 0);
    	}

    	return 0;
}
    	
