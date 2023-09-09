/*
============================================================================
Name : 13.c
Author : Saurabh Varade
Description : Write a program to wait for a STDIN for 10 seconds using select. 
	      Write a proper print statement to verify whether the data is 
	      available within 10 seconds or not (check in $man 2 select).
Date: 25th Aug, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int main() {
	fd_set stdin_set;
	struct timeval tlimit;

	FD_ZERO(&stdin_set);
	FD_SET(0, &stdin_set);
	
	tlimit.tv_sec = 10;
	
	int out = select(1, &stdin_set, NULL, NULL, &tlimit);
	if(out) {
		printf("Data is available\n");
	}
	else {
		printf("No data available\n");
	}

	
	return 0;
}
