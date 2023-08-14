#include <unistd.h>
#include <stdio.h>

int main(void){
	if(!fork()){
		printf("child pid: %d\n",getpid());
		printf("before orphan child ppid: %d\n", getppid());
		sleep(3);
		printf("after orphan child ppid: %d\n",getppid());
	}
	else
		sleep(1);
		printf("parent pid: %d\n", getpid());
}
