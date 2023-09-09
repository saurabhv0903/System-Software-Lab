/*
============================================================================
Name : 8.c
Author : Saurabh Varade
Description : Write a program to open a file in read only mode, read line by line 
		and display each line as it is read. 
		Close the file when end of file is reached.

Date: 14th Aug, 2023
============================================================================
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#define FILENAME Employee.txt

int main(int argc, char* argv[]){
	int fd_read = open(argv[1], O_RDONLY);
	if(fd_read==-1){
		perror("Error: ");
		return -1;
	}
	int eof=0;
	while(!eof){
		char buff;
		while(1){
			int r=read(fd_read, &buff,1);
			if(r==0){
				eof=1;
				break;
			}
			else{
				printf("%c",buff);
				if(buff=='\n'){
					break;
				}
			}
		}
	}

	int close_fd=close(fd_read);
	if(close_fd==-1){
		perror("Error: ");
	}


return 0;
}
