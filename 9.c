#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

int main(){
	
	char path[100];
	struct stat info;
//	scanf("%s",path);

	if(stat("f7s.txt", &info)==-1){
	perror("stat");
	return 0;
	}

	printf("%lu",info.st_ino);
	printf("Number of Hard Links: %lu\n", info.st_nlink);
        printf("uid: %u\n", info.st_uid);
    	printf("gid: %u\n", info.st_gid);
    	printf("size: %lld bytes\n", (long long)info.st_size);
    	printf("block size: %ld bytes\n", (long)info.st_blksize);
    	printf("Number of Blocks: %lld\n", (long long)info.st_blocks);
    	printf("time of last access: %s", ctime(&info.st_atime));
    	printf("time of last modification: %s", ctime(&info.st_mtime));
    	printf("time of last change: %s", ctime(&info.st_ctime));

	return 0;
}
