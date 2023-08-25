#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
	while(1){
        
	creat("/home/saurabhv/Ss_Lab/io_files/f1.txt",O_RDWR);
	creat("/home/saurabhv/Ss_Lab/io_files/f2.txt",O_RDWR);
	creat("/home/saurabhv/Ss_Lab/io_files/f3.txt",O_RDWR);
	creat("/home/saurabhv/Ss_Lab/io_files/f4.txt",O_RDWR);
	creat("/home/saurabhv/Ss_Lab/io_files/f5.txt",O_RDWR);
	sleep(10);

	}
	return 0;
}
