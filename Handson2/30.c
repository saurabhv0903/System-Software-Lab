/*
Name : 30.c
Author : Saurabh Varade
Description : Write a program to create a shared memory.

Date: 10th October, 2023
============================================================================
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
	int shmid;
        key_t key;
        char *shared_memory;

        // Generate a unique key for the shared memory segment
        key = ftok(".", 'A');

    	if (key == -1) {
        	perror("ftok");
        	exit(1);
    	}

    	// Create a shared memory segment
    	shmid = shmget(key, 1024, IPC_CREAT | 0666); // Create with read and write permissions

    	if (shmid == -1) {
        	perror("shmget");
        	exit(1);
    	}

    	// Attach to the shared memory
    	shared_memory = (char *)shmat(shmid, NULL, 0);

    	if (shared_memory == (char *)(-1)) {
        	perror("shmat");
        	exit(1);
    	}

    	// Write data to the shared memory
    	strcpy(shared_memory, "Hello, this is the shared memory data.");

    	printf("Data written to shared memory: %s\n", shared_memory);

    	// Detach from the shared memory with read-only access
    	if (shmdt(shared_memory) == -1) {
        	perror("shmdt");
        	exit(1);
    	}

    	printf("Detached from shared memory.\n");

    	// Attach with O_RDONLY
    	shared_memory = (char *)shmat(shmid, NULL, SHM_RDONLY);

    	if (shared_memory == (char *)(-1)) {
        	perror("shmat");
        	exit(1);
    	}

    	printf("Attached with read-only access. Data: %s\n", shared_memory);

    	// Detach from the shared memory
    	if (shmdt(shared_memory) == -1) {
        	perror("shmdt");
        	exit(1);
    	}

    	printf("Detached from shared memory.\n");

    	// Remove the shared memory segment
    	if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        	perror("shmctl IPC_RMID");
        	exit(1);
    	}

    	printf("Shared memory removed.\n");

    	return 0;
}

