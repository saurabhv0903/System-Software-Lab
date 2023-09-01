#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	
	int cpid = fork();
	
	//fork returns zero to child process and pid of child to parent process. 
	//If will run for child process.
	
	if(!cpid){
		printf("I am child, PID: %d\n", getpid());
	}
	
	else{
		printf("This is a parent process: %d\n", getpid());

		//sleep is written to make the parent wait 
		//so that child will complete its execution 
		//and become a zombie process
		sleep(50);
		//wait(0);
		
	}
	
	//do \"ps <child_pid>\" in terminal to check the status of the program. 
	//if status is Z, it is zombie process	
	return 0;
}
