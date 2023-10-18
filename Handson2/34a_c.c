/*
============================================================================
Name : 34a_c.c
Author : Saurabh Varade
Description :  Write a program to create a concurrent server.
 		a. use fork

Date: 18th Oct, 2023.

============================================================================
*/
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>    
#include <string.h>  
#include <unistd.h>     

int  main()
{
    struct sockaddr_in add;
    char buff[100];
    
    int fd1 = socket(AF_INET, SOCK_STREAM, 0);
    if (fd1 == -1)
    {
        perror("Error while creating socket!");
        return 0;
    }
    
    printf("Client side socket creation success!\n");
    
    add.sin_addr.s_addr = htonl(INADDR_ANY);
    add.sin_family = AF_INET;
    add.sin_port = htons(8080);

    int connectStatus = connect(fd1, (struct sockaddr *)&add, sizeof(add));
    
    if (connectStatus == -1)
    {
        perror("Error while connecting to server!");
        return 0;
    }
    
    printf("Client to server connection success\n");

    size_t readBytes = read(fd1, buff, 100);
    
    if (readBytes == -1){
        perror("Error reading ");
        return 0;
    }
    else{
        printf("Data from server: %s\n", buff);
    }
    
    getchar();
    
    size_t writeBytes = write(fd1, "Hello I'm client!", strlen("Hello I'm client!"));
    if (writeBytes == -1){
        perror("Error while writing ");
        return 0;
    }
    else
        printf("Data sent to server!");

    close(fd1); 
    return 1;
}



