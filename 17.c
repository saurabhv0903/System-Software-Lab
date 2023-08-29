#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define FNAME "/home/saurabhv/Ss_Lab/io_files/17_ticket.txt"

struct data{
	int ticket;
};
int main(){
	
        int fd = open(FNAME, O_RDWR);
        if(fd==-1){
                printf("Failed to open the file");
        }

	struct flock lock;
	
   	lock.l_type = F_WRLCK;
   	lock.l_whence = SEEK_SET;
   	lock.l_start = 0;
   	lock.l_len = 0;
	lock.l_pid = getpid();

	fcntl(fd,F_SETLKW,&lock);
        struct data ticket_info;
        read(fd, &ticket_info, sizeof(ticket_info));

	printf("Value of ticket before: %d\n",ticket_info.ticket);
        ticket_info.ticket++;

	lseek(fd, 0L, SEEK_SET);	

	printf("Value of ticket after: %d\n",ticket_info.ticket);
	write(fd, &ticket_info, sizeof(ticket_info));
	
	printf("Press enter to unlock");
	getchar();
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	
	printf("done\n");
   	
        close(fd);

        return 0;
}

