/*
============================================================================
Name : 22_a.c
Author : Saurabh Varade
Description : Write a program to wait for data to be written into FIFO within 10 seconds, 
              use select system call with FIFO.

Date: 9th October, 2023
============================================================================
*/


#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define max_buffsize 300

int main(){

	char buff[max_buffsize];

	int fd = open("myfifo_mknod", O_WRONLY);

	if(fd == -1){
		printf("erorrrrrrrrrrr");
	}

	printf("Enter the message");
	
	scanf(" %[^\n]", buff);
	write(fd, buff, sizeof(buff));
	
	return 0;
}










