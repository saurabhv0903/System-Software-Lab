#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
	
	if(!fork()){
		
		int child_pid = getpid();
		printf("Child started. Child process id: %d\n", child_pid);

		//ppid will print the process id of the parent 
		printf("Before becoming orphan, parent id for child process: %d\n", getppid());
		printf("\n");
		
		sleep(1);
		
		int orphan_pid = getppid();

		//after parent completes the execution. child will go to systemmd whose process id is 1
		printf("After becoming orphan, parent id for child process: %d\n", orphan_pid);
		printf("Child process stopped\n");
	}

	else{	
		int parent_pid = getpid();
		printf("Parent process id: %d\n", parent_pid);
		printf("\n");

		//sleep is used because parent completes its execution very fast in this program
		//we cannot see the change in the process id of the parent for the child.
		sleep(1);
		exit(0);
			
	}
	
	
	return 0;
}
