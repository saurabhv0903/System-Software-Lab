#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define FNAME "/home/saurabhv/Ss_Lab/io_files/file4.txt"

int main(){
	struct flock lock;
	int fd=open(FNAME,O_RDWR);
   	lock.l_type = F_WRLCK;
   	lock.l_whence = SEEK_SET;
   	lock.l_start = 0;
   	lock.l_len = 0;
	lock.l_pid = getpid();
	printf("Before entering criticl section\n");
	fcntl(fd,F_SETLKW,&lock);
	printf("inside critical section\n");
	printf("Enter to unlock\n");
	getchar();
	printf("unlocked\n");
	lock.l_type=F_UNLCK;
	fcntl(fd,F_SETLK,&lock);
	printf("done\n");

	return 0; 
}
