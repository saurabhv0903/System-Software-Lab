/*
============================================================================
Name : 16.c
Author : Saurabh Varade
Description : Write a program to send and receive data from parent to child vice versa. 
	      Use two way communication.

Date: 9th October, 2023
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
        int fd1[2];
	int fd2[2];

        //buff to take input from command line
        char buff1[20];

        char buff2[20];

        //initialising pipe
        int perr = pipe(fd1);
	int perr1 = pipe(fd2);

        if (perr == -1 || perr1 == -1)
        {
                perror("pipe erorrrrrrrr");          //returns -1 on error
                exit(1);
        }


        if(!fork()){
		close(fd1[0]);
		close(fd2[1]);

		printf("\nChild writing to parent. Enter the message: ");
		scanf("%[^\n]", buff1);
		
		write(fd1[1], buff1, sizeof(buff1));
		
		read(fd2[0], buff2, sizeof(buff2));
		
		printf("Message to child from parent: %s\n", buff2);
	}
	
	else{
                close(fd1[1]);
                close(fd2[0]);
		
		read(fd1[0], buff2, sizeof(buff2));
                printf("Message to child from parent: %s\n", buff2);

                printf("\nParent writing to child. Enter the message: ");
                scanf("%[^\n]", buff1);
                
		write(fd2[1], buff1, sizeof(buff1));
               
        }


        return 0;
}

