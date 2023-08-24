#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{

	int v = symlink("dest.txt","destSL.txt");
	if(v<0){
		perror("Failed");
		return 1;
	}
	if(v==0){
		printf("soft link created\n");
	}


	int f = link("dest.txt","destHL.txt");
	if(f<0){
		perror("Failed");
		return 1;
	}
	if(f==0){
		printf("yayy hard link\n");
	}



	int e = mknod("destFIFO",S_IFIFO|0666,0);    //returns -1 for failure , 0 on success
	if(e<0)
		perror("Failed");
	if(v==0){
		printf("FIFO created\n");
	}

	
	return 0;
}

