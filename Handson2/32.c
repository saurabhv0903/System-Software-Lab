/*
============================================================================
Name : 32.c
Author: Saurabh Varade
Description : Write a program to implement semaphore to protect any critical section.
		a. rewrite the ticket number creation program using semaphore
		b. protect shared memory from concurrent write access
		c. protect multiple pseudo resources ( may be two) using counting semaphore
		d. remove the created semaphore
Date: 18 Oct 2023
============================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

int main() {
	char *shm = shmat(1, (void*)0, 0);
	int initial = 0;
	memcpy(shm, &initial, sizeof(initial));

	int semid = 2;
	/*
	int set_res = semctl(semid, 0, SETVAL, 1);
	if(set_res == -1) {
		perror("Error setting initial value: ");
		return -1;
	}
	*/
	struct sembuf wait = {0, -1, 0};
	printf("Entering critical section\n");
	if(semop(semid, &wait, 1) == -1) {
		perror("Error waiting for semaphore\n");
		return -1;
	}
	printf("Entered critical section");
	int ticket;
	memcpy(&ticket, &shm, sizeof(ticket));
	printf("Current ticket value: %d\n", ticket);
	ticket++;
	printf("New ticket value: %d\n", ticket);
	memcpy(shm, &ticket, sizeof(ticket));
	printf("Press any key to release critical section\n");
	getchar();
	struct sembuf signal = {0, 1, 0};
	if(semop(semid, &signal, 1) == -1) {
		perror("Error signalling semaphore: ");
		return -1;
	}
	printf("Critical section release\n");
	return 0;
}
