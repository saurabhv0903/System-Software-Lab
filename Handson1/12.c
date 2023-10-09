/*
============================================================================
Name : 12.c
Author : Saurabh Varade
Description : Write a program to find out the opening mode of a file. Use fcntl

Date: 24th Aug, 2023
============================================================================
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define FNAME "/home/saurabhv/Ss_Lab/io_files/file4.txt"  

int main(){

	int fd = open(FNAME, O_RDWR);
	int mode = fcntl(fd, F_GETFL);
	switch(mode){
    		case 32768 : 
			printf("r\n"); 
			break;
    		case 32769 : 
			printf("w\n"); 
			break;
    		case 33793 : 
			printf("a\n"); 
			break;
    		case 32770 : 
			printf("r+ || w+\n"); 
			break;
    		case 32794 : 
			printf("a+\n"); 
			break;
	}
	
	return 0;
}
