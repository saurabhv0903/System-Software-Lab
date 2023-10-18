/*
============================================================================
Name : 34a_s.c
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
#include <unistd.h>     
#include <string.h>



int main()
{
    struct sockaddr_in add, client;

    int fd1 = socket(AF_INET, SOCK_STREAM, 0);
    if (fd1 == -1)
    {
        perror("Error while creating socket!");
        return 0;
    }
    printf("Server side socket successfully created!\n");

    add.sin_addr.s_addr = htonl(INADDR_ANY);
    add.sin_family = AF_INET;
    add.sin_port = htons(8080);

    int bindStatus = bind(fd1, (struct sockaddr *)&add, sizeof(add));
    if (bindStatus == -1)
    {
        perror("Error while binding");
        return 0;
    }
    printf("Binding to socket was successful!\n");

    int listenStatus = listen(fd1, 2);
    if (listenStatus == -1)
    {
        perror("Error while trying ");
        return 0;
    }
    printf("Now listening for connections on a socket!\n");
    char buff[1024]; 
     while (1)
    {
        int clientSize = (int)sizeof(client);
        int fd2 = accept(fd1, (struct sockaddr *)&client, &clientSize);
        if (fd2 == -1){
            perror("Error while accepting ");
            return 0;
        }
        else
        {
            if (fork() == 0)
            {
                // Child
                size_t writeBytes = write(fd2, "Hello client,I'm the server!", strlen("Hello client,I'm the server!"));
                if (writeBytes == -1){
                    perror("Error while writing");
                    return 0;
                }
                else
                    printf("Data sent to client!\n");

                size_t readBytes = read(fd2, buff, 100);
                if (readBytes == -1){
                    perror("Error while reading from network via socket!");
                    return 0;
                }
                else
                    printf("Data from client: %s\n", buff);
            }
            else
            {
                // Parent
                close(fd2);
            }
        }

       
    }

    close(fd1);
    return 1;
}



