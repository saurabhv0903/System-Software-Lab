/*
============================================================================
Name : 3_filesdes.c
Author : Saurabh Varade
Description : Write a program to create a file and print the file descriptor value. 
		Use creat ( ) system call

Date: 14th Aug, 2023
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
int main(){
	int fd=creat("/home/saurabhv/Ss_Lab/io_files/a.txt",O_RDONLY | O_WRONLY | O_RDWR);
        printf("fd  = %d\n",fd);
	
	int fd1=creat("/home/saurabhv/Ss_Lab/io_files/b.txt",O_RDONLY | O_WRONLY | O_RDWR);
        printf("fd1  = %d\n",fd1);
	
	return 0;
}
