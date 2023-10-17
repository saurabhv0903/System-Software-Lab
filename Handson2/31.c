/*
============================================================================
Name : 31.c
Author: Saurabh Varade
Description : Write a program to create a semaphore and initialize value to the semaphore.
		a. create a binary semaphore
		b. create a counting semaphore
Date: 18 Oct 2023
============================================================================
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
	key_t key_binary = ftok(".", 12);
	
	int binary = semget(key_binary, 1, IPC_CREAT);
	
	if(binary == -1) {
		perror("Error in creating binary semaphore: ");
		return -1;
	}

	int res_set = semctl(binary, 0, SETVAL, 1);
	if(res_set == -1) {
		perror("Error setting binary semaphore: ");
		return -1;
	}
	printf("Binary semaphore created\n");

	key_t key_counting = ftok(".", 13);
	
	int counting = semget(key_counting, 1, IPC_CREAT);
	if(counting == -1) {
		perror("Error in creating counting semaphore: ");
		return -1;
	}
	
	res_set = semctl(counting, 0, SETVAL, 10);
	if(res_set == -1) {
		perror("Error setting value of counting semaphore: ");
		return -1;
	}
	
	printf("Couting semaphore created\n");
	return 0;
}
