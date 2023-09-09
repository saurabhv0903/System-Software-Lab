/*
============================================================================
Name : 30.c
Author : Saurabh Varade
Description : Write a program to run a script at a specific time using a Daemon process

Date: 9th Sept, 2023
============================================================================
*/


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/time.h>


int main(){
	int inp;
	printf("Enter the number of nimutes after which you want to run the task:");
        scanf("%d",&inp);

        if(!fork()){
                setsid();
                chdir("/");
                //umask(0);

		printf("Inside daemon process\n");
		struct timeval now;
    		int rc;
		
    		rc=gettimeofday(&now, NULL);			//gives current time
    		
		if(rc==0) {
        		printf("gettimeofday() successful.\n");
        		printf("current time in seconds.milliseconds = %lu.%06lu\n",now.tv_sec, now.tv_usec);
    		}
    		else {
        		printf("gettimeofday() failed\n");
        		return -1;
    		}
		
		//int inp;
		//scanf("%d",&inp);

		int newtime = now.tv_sec + inp*60;		//setting the target time to prev time + input minutes

		while(newtime!=now.tv_sec){			
			rc = gettimeofday(&now, NULL);

			if(newtime==now.tv_sec){
				printf("Task executed successfully after %d minutes\n", inp);
				printf("After executing the task current time is: %lu\n",now.tv_sec);
			}
		}

	}
        
	else
                exit(0);
	printf("outside daemon\n");
        return 0;
}

