#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){

	int ppid = getpid();
	printf("Parent process is: %d\n",ppid);

	int cpid=fork();

	if(!cpid){

		printf("Child process id: %d\n",cpid);
	}
	
	return 0;
}
