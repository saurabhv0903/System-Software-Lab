/*
============================================================================
Name : 16.c
Author : Saurabh Varade
Description : Write a program to perform mandatory locking.
 		a. Implement write lock
 		b. Implement read lock
Date: 25th Aug, 2023.
============================================================================
*/


#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define FNAME "/home/saurabhv/Ss_Lab/io_files/file4.txt"

int main(){
	struct flock lock;
	
	int fd=open(FNAME,O_RDWR);
	if(fd==-1){
		printf("file open erorrrrrrr\n");
	}
	
	int inp;
	printf("Enter 1 to read and 2 to write\n");
	scanf("%d", &inp);

	if(inp==2){	
		lock.l_type = F_WRLCK;				//write lock
		printf("Implemented write lock\n");
	}
	else if(inp==1){
		lock.l_type = F_RDLCK;
		printf("Implemented read lock\n");
	}
	else {
		printf("Enter r or w\n");
		return 0;
	}
	
   	lock.l_whence = SEEK_SET;

	//start indicates the start of lock. therefore it is zero. keeping len 0 
	//means applying the lock on the entire file from start. 
	
   	lock.l_start = 0;
   	lock.l_len = 0;
	lock.l_pid = getpid();
	
	printf("Before entering criticl section\n");
	
	fcntl(fd,F_SETLKW,&lock);			//setlkw will wait for the lok to be released
	
	printf("inside critical section\n");
	
	printf("Enter to unlock\n");
	getchar();
	getchar();
	
	printf("unlocked\n");
	lock.l_type=F_UNLCK;
	
	//setlk will relase the lock if l_type is F_UNLCK and aquire the lock if type is F_RDLCK or F_WRLCK
	int fcntlr = fcntl(fd,F_SETLK,&lock);
	
	printf("%d\n",fcntlr);
	printf("done\n");

	return 0; 
}
