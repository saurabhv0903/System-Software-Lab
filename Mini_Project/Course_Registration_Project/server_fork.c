#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Functions/admin_login.c"
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Functions/student_login.c"
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Functions/faculty_login.c"

#define PORT 8085
#define MAX_CLIENTS 20
#define BUFFER_SIZE 4096

void handle_client(int client_socket) {
    // char buffer[BUFFER_SIZE];
    char read_buffer[BUFFER_SIZE];
    char write_buffer[BUFFER_SIZE];
    int bytes_received;

    while (1) {

        //sending menu to the client
        char send_menu[] = "Login as:\n1. Admin\n2. Student \n3. Teacher \n";
        send(client_socket, send_menu, sizeof(send_menu), 0);

        //clearing the read_buffer and receving from the client
        bzero(read_buffer, sizeof(read_buffer));
        int n = recv(client_socket, read_buffer, sizeof(read_buffer), 0);

        //replacing the \n with \0 in the read_buffer to avoid garbage value
        if (strchr(read_buffer, '\n') != NULL) {
            read_buffer[strlen(read_buffer) - 1] = '\0';
        }


        switch (read_buffer[0]) {
            case '1': {
                // char response[] = "You selected Admin";
                // send(client_socket, response, sizeof(response), 0);
                admin_login(client_socket);
                break;
            }
            case '2': {
                student_login(client_socket);
                break;
            }
            case '3': {
                faculty_login(client_socket);
                break;
            }
            default: {
                char response[] = "Invalid choice. Please select a valid option.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
        }

/*
        // Handle client's choice here and send responses accordingly
        if (strcmp(read_buffer, "1") == 0) {
            
            char response[] = "You selected Admin.";
            send(client_socket, response, sizeof(response), 0);
            printf("\n HIiiiii\n");
            admin_login(client_socket);
        } 
        
        else if (strcmp(read_buffer, "2") == 0) {
            char response[] = "You selected Student\n";
            send(client_socket, response, sizeof(response), 0);
        } 
        
        else if (strcmp(read_buffer, "3") == 0) {
            char response[] = "You selected Teacher\n";
            send(client_socket, response, sizeof(response), 0);
        } 
        
        else {
            char response[] = "Invalid choice. Please select a valid option.\n";
            send(client_socket, response, sizeof(response), 0);
        }
*/
    }

    close(client_socket);
    exit(0);
}

int main(int argc, char **argv) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pid_t child_pid;

    // Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(1);
    }
    
	if(argc != 2){
		printf("Usage: %s <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
    int port = atoi(argv[1]);
    
    // Initialize the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        close(server_socket);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, MAX_CLIENTS) == -1) {
        perror("Listening failed");
        close(server_socket);
        exit(1);
    }

    printf("Server is listening on port %d...\n", port);

    while (1) {
        // Accept a client connection
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Accepting client connection failed");
            continue;
        }

        printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Fork a child process to handle the client
        child_pid = fork();
        if (child_pid < 0) {
            perror("Forking failed");
            close(client_socket);
        } else if (child_pid == 0) {
            // In the child process
            close(server_socket);  // Close the server socket in the child process
            handle_client(client_socket);
        } else {
            // In the parent process
            close(client_socket);  // Close the client socket in the parent process
        }
    }

    close(server_socket);
    return 0;
}
