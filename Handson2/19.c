#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){

	const char *fifo = "myfifo";

	int error = mkfifo(fifo, 0666);

	if(error == 0) {
		printf("FIFO %s created\n", fifo);
	}

	else{
		perror("Errorrrrr creating FIFO\n");
		return 1;
	}


	const char *fifo1 = "myfifo1";

	//third parameter is dev which tells the number of device numbers. for FIFO it is set to 0
	int error1 = mknod(fifo1, S_IFIFO | 0666, 0);

	if(error1 == 0){
		printf("FIFO %s created\n", fifo1);
	}

	else{
		perror("Erorrrrrrrr creating FIFO\n");
		return 1;
	}

	return 0;
}

