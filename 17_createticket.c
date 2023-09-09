/*
============================================================================
Name : 17_createticket.c
Author : Saurabh Varade
Description : Write a program to simulate online ticket reservation.
                Implement write lock
                Write a program to open a file, store a ticket number and exit.
                Write a separate program, to open the file, implement write lock,
                read the ticket number, increment the number and print
                the new ticket number then close the file.

Date: 25th Aug, 2023.
============================================================================
*/


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){

	struct{
		int ticket;
	}data;
	data.ticket=1;
	
	int fd = open("17_ticket.txt", O_CREAT, O_RDWR);
	if(fd==-1){
		printf("Failed to open the file");
	}

	write(fd, &data, sizeof(data));
	close(fd);

	return 0;
}
