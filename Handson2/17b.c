/*
============================================================================
Name : 17b.c
Author : Saurabh Varade
Description : Write a program to execute ls -l | wc.
		a. use dup
		b. use dup2
		c. use fcntl
Date: 18 Oct 2023
============================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int pipe_fd[2];
    int res = pipe(pipe_fd);

    if(res < 0) {
        printf("Error in pipe\n");
        return -1;
    }

    if(!fork()) {
        close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
		
	execlp("ls", "ls", "-l", (char*) NULL);
    }
    else {
        close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
        execlp("wc", "wc", (char *) NULL);
    }

    return 0;
}
