/*
============================================================================
Name : 25.c
Author : Saurabh Varade
Description : Write a program to create three child processes. 
		The parent should wait for a particular child (use 
		waitpid system call)

Date: 9th Sept, 2023
============================================================================
*/


#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void Child_process(int child_no, int child_wait) {

        int pid = getppid();

        printf("-------------------------------------------------------\n");
        printf("Child number %d created with PID: %d\n", child_no, getpid());

        //if this is chlid for which we want our parent to wait then use sleep so that we can see that parent is waiting
        if(child_wait == child_no) {

                sleep(5); 
		if(pid != 1) printf("Inside Child number %d, Parent PID: %d, means parent still exists\n",child_no, pid);
                sleep(10); 
		printf("Child number %d stopped\n", child_no);
        }

        else printf("Child number %d stopped\n", child_no);

}

int main() {

        int child, forks[4], status;
        printf("Enter the child number for which you want the parent to wait (1,2,3): ");
        scanf("%d", &child);

        for (int i = 1; i <= 3; i++) {
        forks[i] = fork();

        if (forks[i] == 0) {
            Child_process(i, child);
            exit(0); // Child process should exit after its work
        }
    }

    //if (getpid() != forks[ch])

        printf("Parent started with PID: %d\n", getpid());
        sleep(5);
        printf("-------------------------------------------------------\n");
        printf("Parent waiting\n");
        waitpid(forks[child], &status, 0); // Wait for the specific child process
        printf("Parent stopped\n");
        printf("--------------------------------------------------------\n");

    return 0;
}
