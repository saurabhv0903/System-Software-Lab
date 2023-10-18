/*
============================================================================
Name : 23.c
Author : Saurabh Varade
Description : Write a program to print the maximum number of files can be opened within a process and
		size of a pipe (circular buffer).

Date: 9th October, 2023
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/types.h>

int main() {
	
	struct rlimit rlm;
        int i = getrlimit( RLIMIT_NOFILE, &rlm );
    
    	if (i == 0) {
        	printf("Maximum number of files that can be opened within the file is: %lld\n", (long long)rlm.rlim_cur);
    	} 
    	else {
        	perror("erorrr getting limit");
    	}


    	int pipe1[2];

    	if (pipe(pipe1) == 0) {
    
        	long pipe_size = fpathconf( pipe1[0], _PC_PIPE_BUF );
        	printf("Size of pipe(circular buffer): %ld bytes\n", pipe_size);
        
		close(pipe1[0]);
        	close(pipe1[1]);
    	} 
    	else {
        	perror("erorr creating pipe");
    	}

    	return 0;
}

