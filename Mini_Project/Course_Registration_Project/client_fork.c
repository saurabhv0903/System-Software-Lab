#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define PORT 8085
#define BUFFER_SIZE 4096

int main(int argc, char **argv) {
    int client_socket;
    struct sockaddr_in server_addr;
    // char buffer[BUFFER_SIZE];
    char read_buffer[BUFFER_SIZE];
    char write_buffer[BUFFER_SIZE];
    int bytes_received;

    //checking if we have entered the port on command line
	if(argc != 2){
		printf("Enter port number as first argument");
		return EXIT_FAILURE;
	}
    int port = atoi(argv[1]);


    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Initialize the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.2"); // Server IP address
    server_addr.sin_port = htons(port);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        close(client_socket);
        exit(1);
    }

    printf("Connected to the server");


    while(1){

        //receive code
        bzero(read_buffer, sizeof(read_buffer));                     //receving first menu for roles
        bytes_received = recv(client_socket, read_buffer, BUFFER_SIZE, 0);    // Receive and display the server's response
        if (bytes_received <= 0) {
            perror("Server disconnected");
            break;
        }

        read_buffer[bytes_received]='\0';                           // Null-terminate the received data
        printf("Server response: %s", read_buffer);                 // Print the server's response
    
    
        //send code
        // fgets(write_buffer, sizeof(write_buffer), stdin);
        scanf("%s", write_buffer);
        send(client_socket, write_buffer, strlen(write_buffer), 0);
    }




/*
    admin authentication codeeeeeeeeeee
    bzero(read_buffer, sizeof(read_buffer));                     //receving first menu for roles
    bytes_received = recv(client_socket, read_buffer, BUFFER_SIZE, 0);    // Receive and display the server's response
    if (bytes_received <= 0) {
        perror("Server disconnected");
    }

    read_buffer[bytes_received]='\0';                           // Null-terminate the received data
    printf("Server response: %s", read_buffer);                 // Print the server's response

    //sending option for role
    scanf("%s", write_buffer);
    send(client_socket, write_buffer, strlen(write_buffer), 0);


    //receive "you are admin" message
    bzero(write_buffer, sizeof(write_buffer));
    bzero(read_buffer, sizeof(read_buffer));

    // Receive and display the server's response
    bytes_received = recv(client_socket, read_buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("Server disconnected");
    }


    read_buffer[bytes_received]='\0';
    //receive admin menu
    bytes_received = recv(client_socket, read_buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("Server disconnected");
    }

    read_buffer[bytes_received]='\0';
    
    // Print the server's response
    printf("Server response: %s", read_buffer);

    //send username details
    scanf("%s", write_buffer);
    send(client_socket, write_buffer, strlen(write_buffer), 0);

    bzero(write_buffer, sizeof(write_buffer));


    //receive password prompt
    bytes_received = recv(client_socket, read_buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("Server disconnected");
        // break;
    }


    read_buffer[bytes_received]='\0';

    
    
    // Print the server's response
    printf("Server response: %s", read_buffer);

    //send password
    scanf("%s", write_buffer);
    send(client_socket, write_buffer, strlen(write_buffer), 0);

    bzero(write_buffer, sizeof(write_buffer));

    bytes_received = recv(client_socket, read_buffer, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("Server disconnected");
    }


*/

    // Close the client socket and exit
    close(client_socket);
    return 0;
}
