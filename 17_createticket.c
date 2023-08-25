#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){

	struct{
		int ticket;
	}data;
	data.ticket=1;
	
	int fd = open("17_ticket.txt", O_RDWR);
	if(fd==-1){
		printf("Failed to open the file");
	}

	write(fd, &data, sizeof(data));
	close(fd);

	return 0;
}
