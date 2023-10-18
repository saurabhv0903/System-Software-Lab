/*
Name : 24.c
Author : Saurabh Varade
Description : Write a program to create a message queue and print the key and message queue id.

Date: 9th October, 2023
============================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main() {
	
	// proj_id will be taken as ascii value of a and to create key we used \".\"
	int key = ftok(".", 'a');
	
	int msgid = msgget(key, IPC_CREAT|IPC_EXCL|0744);
	
	// %0x is used for hexadecimal value
	printf("\nkey=0x%0x\t msgid=%d\n", key, msgid);
	
	return 0;
}
