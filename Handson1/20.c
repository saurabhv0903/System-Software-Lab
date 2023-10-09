/*
============================================================================
Name : 20.c
Author : Saurabh Varade
Description : Find out the priority of your running program. 
		Modify the priority with nice command

Date: 1st Sept, 2023
============================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int main(){

	//first parameter is for process, if we want group process priority use PRIO_PGRP. 
	//But we want the prioirty for process, hence PRIO_PROCESS
	//second parameter is 0 because we want the priority for the current process
		
	int priority = getpriority(PRIO_PROCESS,0);
	
	printf("Current priority is: %d\n",priority);
	
	printf("Enter the nice value to change the priority: ");
	int inp;
	
	scanf("%d",&inp);
	
	//nice changes the priority for the current process and returns the updated process priority.
	//priority range is from -20 to 19
	int pr = nice(inp);
	
	printf("Current prioirty is: %d\n",pr);
	return 0;
}
