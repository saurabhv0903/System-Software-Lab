#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
  
int main()
{
	int pipebuf[2]; 
	
	//buff to take input from command line
	char buff[10];

	char rbuff[10];
	
	//we are reading the input till end of line	
	scanf("%[^\n]", buff);

	//initialising pipe
	int perr=pipe(pipebuf);

	if (perr == -1) 
	{
        	perror("pipe erorrrrrrrr");          //returns -1 on error
        	exit(1); 
        }
  
    
        write(pipebuf[1], buff, sizeof(buff)); 		//writing into the pipe at index 1 of pipebuf
        printf("\n");
  	
        read(pipebuf[0], rbuff, 6);			// read happens at pipe index 0 of pipebuf
  
        printf("Content in the pipe: %s\n", rbuff); 

	return 0;
}
