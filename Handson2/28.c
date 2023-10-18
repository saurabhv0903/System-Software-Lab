/*
Name : 28.c
Author : Saurabh Varade
Description : Write a program to change the exiting message queue permission. 
		(use msqid_ds structure)

Date: 10th October, 2023
============================================================================
*/



#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    key_t key;
    int msqid;

    //use the same key used before
    key = ftok(".", 'b');

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msqid = msgget(key, 0666 | IPC_CREAT);

    if (msqid == -1) {
        perror("msgget erorr");
        exit(1);
    }

    //defining msqid_ds    
    struct msqid_ds msq_attr;

    //get current attributes
    if (msgctl(msqid, IPC_STAT, &msq_attr) == -1) {
        perror("msgctl IPC_STAT");
        exit(1);
    }

    //changing the permission of message queue
    msq_attr.msg_perm.mode = 0644; 

    //update the attributes of the message queue
    if (msgctl(msqid, IPC_SET, &msq_attr) == -1) {
        perror("msgctl ipc set");
        exit(1);
    }

    printf("Permissions of message queue updated\n");

    return 0;
}

