#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FNAME "file4.txt"

int main(){ 
    int filedes;
    filedes=open(FNAME, O_RDWR);
    if(filedes==-1){
    	perror("Failed\n");
    }
    else{
    	printf("File opened\n");
    }

    char buf[10]="Hello hii";
    int char_write = write(filedes, buf, 10);
    printf("write 1 value: %d \n",char_write);

    int lseekreturn = lseek(filedes, 10, SEEK_CUR);
    printf("lseek return value: %d \n",lseekreturn);
    
    int char_write2 = write(filedes, buf, 10);
    printf("write 2 value: %d \n",char_write2);


return 0;
}

