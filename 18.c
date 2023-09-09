/*
============================================================================
Name : 18.c
Author : Saurabh Varade
Description : Write a program to simulate online ticket reservation.
                Implement write lock
                Write a program to open a file, store a ticket number and exit.
                Write a separate program, to open the file, implement write lock,
                read the ticket number, increment the number and print
                the new ticket number then close the file.

Date: 25th Aug, 2023
============================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define FNAME "/home/saurabhv/Ss_Lab/io_files/record.txt"
struct data {
	int val;
};

int main() {
	int fd = open(FNAME, O_RDWR);
	while(1) {
		int option;
		printf("Enter record (1-3) to lock, or -1 to quit: ");
		scanf("%d", &option);
		if(option == -1) {
			break;
		}
		
		//set the offset to the record we want to change
		int offset = (option - 1) * sizeof(struct data);
		lseek(fd, offset, SEEK_SET);
		
		printf("Acquiring record lock\n");
		
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = offset;
		lock.l_len = sizeof(struct data);
		lock.l_pid = getpid();
		
		fcntl(fd, F_SETLK, &lock);
		printf("Lock acquired\n");
		
		//initializing a struct currRecord to take the value of the record, update it and then writing it to the file.
		struct data currRecord;
		//reading the record to currRecord
		read(fd, &currRecord, sizeof(currRecord));
		printf("Previous value of record: %d\n", currRecord.val);
		//updating the value of the currRecord
		currRecord.val++;
		printf("Current value of record: %d\n", currRecord.val);
		
		//taking the pointer to the record we want to change
		lseek(fd, -sizeof(struct data), SEEK_CUR);
		
		//writing the updated value
		write(fd, &currRecord, sizeof(currRecord));
		printf("Releasing record lock\n");
		lock.l_type = F_UNLCK;
		fcntl(fd, F_SETLK, &lock);
		printf("Lock released\n");
	}
	return 0;
}
		
