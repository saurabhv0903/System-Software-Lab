/*
============================================================================
Name : 4_readwrite.c
Author : Saurabh Varade
Description :  Write a program to open an existing file with read write mode. 
		Try O_EXCL flag also. 

Date: 14th Aug, 2023
============================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FNAME "/home/saurabhv/Ss_Lab/io_files/file4.txt"

int main(){ 
    int filedes;
    filedes=open(FNAME, O_EXCL, O_RDWR);
    if(filedes==-1){
    	perror("Failed");
    }
    else{
    	printf("File opened");
    }
    printf("%d\n",filedes);
return 0;
}
