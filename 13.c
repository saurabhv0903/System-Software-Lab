#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int main() {
	fd_set stdin_set;
	struct timeval tlimit;

	FD_ZERO(&stdin_set);
	FD_SET(0, &stdin_set);
	
	tlimit.tv_sec = 10;
	
	int out = select(1, &stdin_set, NULL, NULL, &tlimit);
	if(out) {
		printf("Data is available\n");
	}
	else {
		printf("No data available\n");
	}

	
	return 0;
}
