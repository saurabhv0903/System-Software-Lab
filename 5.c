#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
	int pid=getpid();
	printf("pid: %d\n",pid);
	while(1){
        	
		int fd1 = creat("/home/saurabhv/Ss_Lab/io_files/f1.txt",O_RDWR);
		int fd2 = creat("/home/saurabhv/Ss_Lab/io_files/f2.txt",O_RDWR);
		int fd3 = creat("/home/saurabhv/Ss_Lab/io_files/f3.txt",O_RDWR);
		int fd4 = creat("/home/saurabhv/Ss_Lab/io_files/f4.txt",O_RDWR);
		int fd5 = creat("/home/saurabhv/Ss_Lab/io_files/f5.txt",O_RDWR);
		printf("fd1: %d , fd2: %d , fd3: %d, fd4: %d, fd5: %d\n",fd1,fd2,fd3,fd4,fd5);
		sleep(30);

	}
	return 0;
}
