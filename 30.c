#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/time.h>


int main(){

        if(!fork()){
                setsid();
                chdir("/");
                //umask(0);

		printf("Inside daemon process\n");
		struct timeval now;
    		int rc;

    		rc=gettimeofday(&now, NULL);
    		
		if(rc==0) {
        		printf("gettimeofday() successful.\n");
        		printf("time = %lu.%06lu\n",now.tv_sec, now.tv_usec);
    		}
    		else {
        		printf("gettimeofday() failed\n");
        		return -1;
    		}

		//while(1){
		//	if()
		//}
        
	}
        
	else
                exit(0);
	printf("outside daemon\n");
        return 0;
}

