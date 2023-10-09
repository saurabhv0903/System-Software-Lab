/*
============================================================================
Name : 6.c
Author : Saurabh Varade
Description : Write a program to take input from STDIN and display on STDOUT. 
		Use only read/write system calls

Date: 14th Aug, 2023
============================================================================
*/

#include <unistd.h>

int main() {
	char buff[10];
	
	//read will read the standard input. enter some text after executing
	read(0, &buff, 10);
	write(1, &buff, 10);
	return 0;
}

