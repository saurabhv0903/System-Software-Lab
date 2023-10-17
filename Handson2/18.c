/*
============================================================================
Name : 18.c
aurabh Varade
Description : Write a program to find out total number of directories on the pwd.
		execute ls -l | grep ^d | wc ? Use only dup2.
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
    int pipe_fd_1[2];
    pipe(pipe_fd_1);

    if(!fork()) {
        dup2(pipe_fd_1[1], 1);
        close(pipe_fd_1[1]);
        execlp("ls", "ls", "-l", (char *) NULL);
    }
    else {
        int pipe_fd_2[2];
        pipe(pipe_fd_2);
        dup2(pipe_fd_1[0], 0);
        close(pipe_fd_1[1]);


        if(!fork()) {
            dup2(pipe_fd_2[1], 1);
	    close(pipe_fd_2[0]);
	    execlp("grep", "grep", "^d", (char *) NULL);
        }
        else {
            dup2(pipe_fd_2[0], 0);
	    close(pipe_fd_2[1]);
	    execlp("wc", "wc", (char *) NULL);
        }
    }

    return 0;
}
