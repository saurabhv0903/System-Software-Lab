/*
============================================================================
Name : 27.c
Author : Saurabh Varade
Description : Write a program to execute ls -Rl by the following system calls
 		a. execl
 		b. execlp
 		c. execle
 		d. execv
 		e. execvp

Date: 1st Sept, 2023
============================================================================
*/


#include <stdio.h>
#include <unistd.h>

int main(){

	int n;
	printf("---------------------Menu---------------------\n");
	printf("1. execl\n");
	printf("2. execlp\n");
	printf("3. execle\n");
	printf("4. execv\n");
	printf("5. execvp\n");

	printf("Enter the option\n");
	scanf("%d",&n);

	switch(n){
		case 1:
			//execl
			printf("-------------execl command--------------\n");
			printf("\n");

			execl("/bin/ls","ls","-Rl",(char *) NULL);
	
			printf("\n");
			break;

		case 2:
			//execlp
			printf("-------------execl command:---------------\n");
			printf("\n");
			execlp("ls","ls","-Rl",(char *) NULL);				//p is path in execlp

			printf("\n");
			break;

		case 3:
			//execle
			printf("-------------execle command:--------------\n");
			printf("\n");
			char *env[] = { "HOME=/usr/home", "LOGNAME=home", (char *)0 };
           		
           		execle ("/bin/ls", "ls", "-Rl", (char *)0, env);		//e is enviornment
			
			printf("\n");
			break;
		
		case 4:
			//execv
			printf("-------------execv command:--------------\n");
                        printf("\n");
			char *cmd[] = { "ls", "-Rl", (char *)0 };
           		
           		execv ("/bin/ls", cmd);
			
                        printf("\n");
                        break;

		case 5:
			//execvp
			printf("-------------execv command:--------------\n");
                        printf("\n");
                        char *cmd1[] = { "ls", "-Rl", (char *)0 };
           		execvp ("ls", cmd1);

                        printf("\n");
                        break;

		}	
	return 0;
}
