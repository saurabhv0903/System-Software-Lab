#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Functions/admin.c"

#define PORT 8085
#define BUFFER_SIZE 4096


int admin_login(int client_socket){

    char buffer[BUFFER_SIZE];
    char admin_username[] = "admin";
    char admin_password[] = "1234";
    char admin_username1[20] ;
    char admin_password1[20] ;
    char menu[300];


    //admin sign in for username
    strcpy(menu, "You selected Admin\nSign in for Admin: Enter Username: ");
    send(client_socket, menu, strlen(menu), 0);

    bzero(buffer, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);

    strcpy(admin_username1,buffer);
    printf("%s\n", admin_username1);
    
    if (strchr(buffer, '\n') != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
    }

    //admin sign in for password
    bzero(menu, sizeof(menu));
    strcpy(menu, "Password: ");
    send(client_socket, menu, strlen(menu), 0);

    bzero(buffer, sizeof(buffer));
    recv(client_socket, buffer, sizeof(buffer), 0);

    if (strchr(buffer, '\n') != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
    }

    strcpy(admin_password1, buffer);
    printf("%s\n", admin_password1);

    if (strcmp(admin_username1, "admin") == 0 && strcmp(admin_password1, "1234") == 0) {
    
        // char response[] = "Admin logged in";
        // send(client_socket, response, sizeof(response), 0);
        admin(client_socket);
    }

    close(client_socket);
    return 0;
}
