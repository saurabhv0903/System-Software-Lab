/*
============================================================================
Name : 15.c
Author : Saurabh Varade
Description : Write a program to display the environmental variable of the user (use environ)
Date: 25th Aug, 2023.
============================================================================
*/


#include <unistd.h>
#include <stdio.h>

extern char **environ;

int main(){
	int i = 0;
	
	while(environ[i]) {
		printf("%s\n", environ[i++]); // prints in form of variable=value
	}

	return 0;
}
