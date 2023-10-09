/*
============================================================================
Name : 14.c
Author : Saurabh Varade
Description : Write a simple program to create a pipe, write to the pipe, 
	      read from pipe and display on the monitor.

Date: 10th September, 2023
============================================================================
*/


#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
  
int main()
{
	int pipebuf[2]; 
	
	//buff to take input from command line
	char buff[30];

	char rbuff[30];
	
	//we are reading the input till end of line	
	scanf("%[^\n]", buff);
	//scanf("%c", buff);

	//initialising pipe
	int perr=pipe(pipebuf);

	if (perr == -1) 
	{
        	perror("pipe erorrrrrrrr");          //returns -1 on error
        	exit(1); 
        }

    
        write(pipebuf[1], buff, sizeof(buff)); 		//writing into the pipe at index 1 of pipebuf
        printf("\n");
  	
        read(pipebuf[0], rbuff, 6);			// read happens at pipe index 0 of pipebuf
  
        printf("Content in the pipe: %s\n", rbuff); 

	return 0;
}


