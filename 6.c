#include <unistd.h>

int main() {
	char buff[10];
	
	//read will read the standard input. enter some text after executing
	read(0, &buff, 10);
	write(1, &buff, 10);
	return 0;
}

