/*
============================================================================
Name : 25_recieve.c
Author : Saurabh Varade
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)

Date: 10th October, 2023
============================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main() {

	struct msg {
		long int m_type;
		char message[80];
	} myq;

	key = ftok(".", 'b');
	mqid = msgget(key, 0);
	
	printf("Enter message type: ");
	scanf("%ld", &myq.m_type);
	ret = msgrcv(mqid, &myq, sizeof(myq.message), myq.m_type, IPC_NOWAIT|MSG_NOERROR);
	
	if (ret == -1)
		exit(-1);
	printf("Message type: %ld\n Message: %s\n", myq.m_type, myq.message);
}


