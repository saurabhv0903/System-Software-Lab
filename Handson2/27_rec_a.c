/*
============================================================================
Name : 27_rec_a.c
Author : Saurabh Varade
Description : Write a program to print a message queue's (use msqid_ds and ipc_perm structures)

Date: 10th October, 2023
============================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>


int main(){

        struct msg{
                long int m_type;
                char message[80];
        } myq;

        int key = ftok ( ".", 'b' );
        int mqid = msgget(key, 0);                //If a message queue with a given key exists and msgflg = 0, then msgget() returns the unique identifier for the message queue

        printf("Enter the message type: \n");
        scanf("%ld", &myq.m_type);

	int ret = msgrcv(mqid, &myq, sizeof(myq.message), myq.m_type, IPC_NOWAIT|MSG_NOERROR);
	if (ret == -1)
		exit(-1);
	
	printf("Message type: %ld\n Message: %s\n", myq.m_type, myq.message);
}




