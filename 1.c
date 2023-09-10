/*
============================================================================
Name : 1_systemcall.c
Author : Saurabh Varade
Description : Create the following types of a files using (i) shell command (ii) system call
 		a. soft link (symlink system call)
 		b. hard link (link system call)
 		c. FIFO (mkfifo Library Function or mknod system call)

Date: 14th Aug, 2023
============================================================================
*/


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{

	int v = symlink("/home/saurabhv/Ss_Lab/io_files/dest.txt","/home/saurabhv/Ss_Lab/io_files/destSL.txt");
	if(v<0){
		perror("Failed");
		return 1;
	}
	if(v==0){
		printf("soft link created\n");
	}


	int f = link("/home/saurabhv/Ss_Lab/io_files/dest.txt","/home/saurabhv/Ss_Lab/io_files/destHL.txt");
	if(f<0){
		perror("Failed");
		return 1;
	}
	if(f==0){
		printf("yayy hard link\n");
	}



	int e = mknod("/home/saurabhv/Ss_Lab/io_files/destFIFO",S_IFIFO|0666,0);    //returns -1 for failure , 0 on success
	if(e<0)
		perror("Failed");
	if(v==0){
		printf("FIFO created\n");
	}

	
	return 0;
}

