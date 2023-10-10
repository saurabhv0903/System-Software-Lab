/*
============================================================================
Name : 21_b.c
Author : Saurabh Varade
Description : Write two programs so that both can communicate by FIFO -Use two way communications.

Date: 9th October, 2023
============================================================================
*/

//run both 21_a.c and 21_b.c simultaneously

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
        char buff1[max_buffsize];

        int fd1 = open("myfifo_mknod", O_RDONLY);
        int fd2 = open("myfifo_mkfifo", O_WRONLY);

        read(fd1, buff, sizeof(buff1));
        printf("Message from FIFO file is\n %s\n", buff);


        printf("Enter the message:\n");
        scanf(" %[^\n]", buff1);
        write(fd2, buff1, sizeof(buff1));

        return 0;
}

