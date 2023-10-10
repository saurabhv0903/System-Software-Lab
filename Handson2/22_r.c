/*
============================================================================
Name : 22_w.c
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

        int fd = open("myfifo_mknod", O_RDONLY);
        
        //writing select
        fd_set rfds;
        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);


        //waiting for data and then reading if data available 
        if(!select(fd+1, &rfds, NULL, NULL, &tv)){
                printf("no data is available from other end\n");
        }
        else{
                read(fd, buff, sizeof(buff));
                printf("Message from FIFO file is\n %s\n", buff);
        }


	return 0;
}
   
