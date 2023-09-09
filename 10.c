/*
============================================================================
Name : 10.c
Author : Saurabh Varade
Description : Write a program to open a file with read write mode, 
		write 10 bytes, move the file pointer by 10 
		bytes (use lseek) and write again 10 bytes. 
 		a. check the return value of lseek
 		b. open the file with od and check the empty spaces in between the data.

Date: 24th Aug, 2023
============================================================================
*/


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FNAME "/home/saurabhv/Ss_Lab/io_files/file4.txt"

int main(){ 
    int filedes;
    filedes=open(FNAME, O_RDWR);
    
    if(filedes==-1){
    	perror("Failed\n");
    }
    else{
    	printf("File opened\n");
    }
    //lseek(filedes, 0L, SEEK_SET);
    
    char buf[10]="Hello hi\n";
    int char_write = write(filedes, buf, 10);
    printf("write 1 value: %d \n",char_write);
    
    int lseekreturn = lseek(filedes, 10, SEEK_CUR);
    printf("lseek return value: %d \n",lseekreturn);
    
    int char_write2 = write(filedes, buf, 10);
    printf("write 2 value: %d \n",char_write2);


return 0;
}

