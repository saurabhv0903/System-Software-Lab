/*
============================================================================
Name : 11.c
Author : Saurabh Varade
Description : Write a program to open a file, duplicate the file descriptor 
		and append the file with both the descriptors 
		and check whether the file is updated properly or not

Date: 25th Aug, 2023
============================================================================
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void readfile(char *file) {
	int fd_read = open(file, O_RDONLY);
	while(1) {
		char buffer;
		int size = read(fd_read, &buffer, 1);
		if(size == 0) {
			break;
		}
		printf("%c", buffer);
	}
}

int f_dup(char *file) {
	int og_fd = open(file, O_RDWR);
	if(og_fd == -1) {
		printf("dup file open erorrrrr\n");
		return -1;
	}

	int dup_fd = dup(og_fd);			//duplicate fd suing dup
	if(dup_fd == -1) {
		printf("duplicating fd failed using dup\n");
		return -1;
	}

	// Write and read using original descriptor
	char og_buff[] = "dup original fd\n";
	int og_write = write(og_fd, &og_buff, sizeof(og_buff));
	printf("Reading after writing using og dup\n");	
	readfile(file);
	printf("\n");
	
	// Write usng dup fd
	char dup_buff[] = "dup duplicate fd\n";
	int dup_write = write(dup_fd, &dup_buff, sizeof(dup_buff));
	printf("Reading after writing using duplicate dup\n");
	readfile(file);

	// Close fds 
	close(og_fd);
	close(dup_fd);
}

int f_dup2(char *file) {
	int og_fd = open(file, O_RDWR);
	
	if(og_fd == -1) {
		printf("dup2 file open erorrrrrrr\n");
		return -1;
	}
	
	int dup_fd = dup2(og_fd, 6);
	if(dup_fd == -1) {
		printf("duplicating fd failed using dup2\n");
		return -1;
	}

	char og_buff[] = "dup2 original fd\n";
	int og_write = write(og_fd, &og_buff, sizeof(og_buff));
	printf("Reading after writing using og dup2\n");	
	readfile(file);
	printf("\n");

	//write using dup2 fd
	char dup_buff[] = "dup2 duplicate buff\n";
	int dup_write = write(dup_fd, &dup_buff, sizeof(dup_buff));
	printf("Reading after writing using duplicate dup\n");
	readfile(file);

	// Close fds
	close(og_fd);
	close(dup_fd);
}

int f_fcntl(char *file) {
	int og_fd = open(file, O_RDWR);
	if(og_fd == -1) {
		printf("fcntl file open erorrrrr\n");
		return -1;
	}

	int dup_fd = fcntl(og_fd, F_DUPFD);
	if(dup_fd == -1) {
		printf("Duplicating fd failed using fcntl\n");
		return -1;
	}

	//using original fd
	char og_buff[] = "fcntl original fd\n";
	int og_write = write(og_fd, &og_buff, sizeof(og_buff));
	printf("Reading after writing using og fcntl\n");
	readfile(file);
	printf("\n");

	// write using fcntl fd
	char dup_buff[] = "fcntl duplicate buff\n";
	int dup_write = write(dup_fd, &dup_buff, sizeof(dup_buff));
	printf("Reading after writing using duplicate fcntl\n");
	readfile(file);

	// Close fds 
	close(og_fd);
	close(dup_fd);
}

int main(int argc, char *args[]) {
	if(argc != 2) {
		printf("Enter 1 argument\n");
		return -1;
	}

	f_dup(args[1]);
	f_dup2(args[1]);
	f_fcntl(args[1]);
	return 0;
}
