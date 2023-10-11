/*
============================================================================
Name : 26_send.c
Author : Saurabh Varade
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)

Date: 10th October, 2023
============================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

int main(){
	
	struct msg{
		long int m_type;
		char message[80];
	} myq;

	int key = ftok ( ".", 'b' );
	int mqid = msgget(key, 0666 | IPC_CREAT);                //If a message queue with a given key exists and msgflg = 0, then msgget() returns the unique identifier for the message queue

	printf("Enter the message type: \n");
	scanf("%ld", &myq.m_type);

	printf("Enter the message text: \n");
	scanf(" %[^\n]", myq.message);
	
	int size = strlen(myq.message);

	//+1 for terminating character
	msgsnd(mqid, &myq, size+1, 0);

	return 0;
}


