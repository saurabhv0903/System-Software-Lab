#include<stdio.h>
#include<sched.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	
	int pid=getpid();
	int currpolicy= sched_getscheduler(0);		//0 is the pid for calling process
	int getparam_status;
	struct sched_param param;

	if(currpolicy==-1){
		printf("policy not found\n");
		return 0;
	}

	printf("Current Scheduling policy is: %d\n", currpolicy);

	getparam_status = sched_getparam(pid, &param);
	printf("getparam status: %d\n",getparam_status);
	printf("param: %d\n", param.sched_priority);
	
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	//struct sched_param new_param;
	//new_param.sched_priority = 50;
	printf("new param: %d\n", param.sched_priority);
	sched_setparam(pid, &param);	

	if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
	        printf("setting scheduler erorrrrrrrrrr\n");
    	}

	int newpriority = sched_getparam(pid, &param);
	printf("new scheduling policy is: %d\n", param.sched_priority);

	return 0;
}
