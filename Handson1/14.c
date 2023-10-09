/*
============================================================================
Name : 14.c
Author : Saurabh Varade
Description : Write a program to find the type of a file.
 		a. Input should be taken from command line.
 		b. program should be able to identify any type of a file

Date: 25th Aug, 2023
============================================================================
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *args[]){
	if(argc!=2){
		printf("Enter one argument\n");
	}
	// stat contains all the info used in 9 th code as well
	struct stat info;

	stat(args[1],&info);
	//we have to do and operation to get the mode
	int stat_info=info.st_mode & S_IFMT;
	
	switch(stat_info) {
		case S_IFBLK:
			printf("Block file\n");
			break;
		case S_IFCHR:
			printf("Character device\n");
			break;
		case S_IFDIR:
			printf("Directory\n");
			break;
		case S_IFIFO:
			printf("FIFO\n");
			break;
		case S_IFLNK:
			printf("Symlink\n");
			break;
		case S_IFREG:
			printf("Regular\n");
			break;
		case S_IFSOCK:
			printf("Socket\n");
			break;
		default:
			printf("Unknow\n");
			break;
	}

	return 0;
}

