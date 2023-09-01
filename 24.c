#include <stdio.h>
       #include <sys/types.h>
       #include <unistd.h>


int main(){
	
	if(!fork()){
		
		int child_pid = getpid();
		printf("Child process id: %d\n", child_pid);
		
		sleep(5);
		
		int orphan_pid = getpid();
		printf("Orphan child process id: %d\n", orphan_pid);

	}

	else{
		
		int parent_pid = getpid();
		printf("Parent process id: %d\n", parent_pid);
		
	}
	
	
	return 0;
}
