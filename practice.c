#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[]){

        if (argc!=2){
                printf("enter 1 arguments");
                return 0;
        }

        //open file
        int fd = open(argv[1], O_RDWR);

        if(fd==-1)
                printf("errorrrr opening file");

        //closing the fd
        int fd_close = close(fd);


        if(fd_close==-1)
                printf("errorrr closing file");

	int fd_close1 = close(fd);
	if(fd_close==-1)
                printf("errorrr closing file2");


        return 0;
}

