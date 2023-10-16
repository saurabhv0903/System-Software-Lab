/*
============================================================================
Name : 22_b.c
Author : Saurabh Varade
Description : Write a program to wait for data to be written into FIFO within 10 seconds, 
	      use select system call with FIFO.

Date: 9th October, 2023
============================================================================
*/

//run both 22_a.c and 22_b.c simultaneously

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define max_buffsize 300

int main(){

	//initializing buffers
        char buff[max_buffsize];

	//initializing fifo
        int fd1 = open("myfifo_mknod", O_RDONLY);

        //writing select
        fd_set rfds;
        struct timeval tv;
        tv.tv_sec = 5;
	tv.tv_usec = 0;
        FD_ZERO(&rfds);
        FD_SET(fd1, &rfds);

	//waiting for data and then reading if data available
	if(!select(fd1+1, &rfds, NULL, NULL, &tv)){
                printf("no data is available from other end");
        }
	else{
        	read(fd1, buff, sizeof(buff));
        	printf("Message from FIFO file is\n %s\n", buff);
	}
	
        return 0;
}

