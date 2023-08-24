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
	printf("Number of Hard Links: %lu\n", file_stat.st_nlink);
        printf("uid: %u\n", file_stat.st_uid);
    	printf("gid: %u\n", file_stat.st_gid);
    	printf("size: %lld bytes\n", (long long)file_stat.st_size);
    	printf("block size: %ld bytes\n", (long)file_stat.st_blksize);
    	printf("Number of Blocks: %lld\n", (long long)file_stat.st_blocks);
    	printf("time of last access: %s", ctime(&file_stat.st_atime));
    	printf("time of last modification: %s", ctime(&file_stat.st_mtime));
    	printf("time of last change: %s", ctime(&file_stat.st_ctime));

	return 0;
}
