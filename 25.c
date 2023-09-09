#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

	int fork1=fork();
	
	if(fork1==0){
		int child1=getpid();
		printf("First child id:%d\n", child1);
	}
	else{
		int fork2=fork();
		if(fork2==0){
			int child2=getpid();

			printf("Second child id:%d\n", child2);

		}
		
		else{
			int status;
			int child3;
			int fork3=fork();
			
			if(fork3==0){
				child3=getpid();
				printf("Third Child id: %d\n", child3);
				sleep(20);
				printf("Third child process execution completed\n");
			}
			
			else{
				printf("Parent process id: %d\n",getpid());
				sleep(5);
				printf("Waiting for Third child\n");
				
				int w = waitpid(fork3, &status, WUNTRACED | WCONTINUED);
            			
				
				printf("Parent stpped waiting\n");
        			exit(EXIT_SUCCESS);
				
			}
		}
	}
	return 0;
}
