#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
// #include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Record_structures/create_student.c"
// #include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Record_structures/create_faculty.c"


#define PORT 8085
#define BUFFER_SIZE 1024

char send_response[BUFFER_SIZE];
char read_response[BUFFER_SIZE];

/*
struct Student{
    char username[50];
    char password[50];
    char name[50];
    int roll;
    int status;
    char course_enrolled[4][30];
};

struct Faculty{
    int id;
    char username[50];
    char password[50];
    char name[50];
    int status;
    char course_offered[4][30];
};

*/



int student_manage(int client_socket){
    char menu[] = "\nStudent logged in\n\nEnter the Option:\n1. Enroll Student\n9. Logout\n";
    send(client_socket, menu, sizeof(menu), 0);

    char buffer[BUFFER_SIZE];

    while (1) {

        bzero(buffer, sizeof(buffer));
        int n = recv(client_socket, buffer, sizeof(buffer), 0);
        if (n <= 0) {
            perror("Client disconnected");
            break;
        }

        if (strchr(buffer, '\n') != NULL) {
            buffer[strlen(buffer) - 1] = '\0';
        }

        int choice = atoi(buffer);

        switch (choice) {
            case 1: {

                add_student(client_socket);
                char response[] = "\nAdded Student.\n\nEnter the Option:\n1. Add Student\n2. Add Faculty\n3. Activate Student\n4. Decativate Student\n5. Update Student Details\n6. Update Faculty Details\n7. View Student\n8. View Faculty\n9. Logout\n";
                send(client_socket, response, sizeof(response), 0);
                
                break;
            }
            case 2: {
                // Add Faculty functionality
                // Implement this functionality here, including data storage
                add_faculty(client_socket);
                char response[] = "Added Faculty.\n\nEnter the Option:\n1. Add Student\n2. Add Faculty\n3. Activate Student\n4. Decativate Student\n5. Update Student Details\n6. Update Faculty Details\n7. View Student\n8. View Faculty\n9. Logout\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 3: {
                // Activate Student functionality
                // Implement this functionality here, including data storage
                char response[] = "Activated Student.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 4: {
                // Deactivate Student functionality
                // Implement this functionality here, including data storage
                char response[] = "Deactivated Student.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 5: {
                // Update Details functionality
                // Implement this functionality here, including data storage
                char response[] = "Updated Student Details.\n";
                
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 6: {
                // Update Details functionality
                // Implement this functionality here, including data storage
                char response[] = "Updated Faculty Details.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 7: {
                // Logout functionality
                char response[] = "View Student Details.\n";
                view_students(client_socket);
                // send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 8: {
                // Logout functionality
                char response[] = "View Faculty Details.\n";
                view_faculty(client_socket);
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 9: {
                // Logout functionality
                char response[] = "Logged out.\n";
                send(client_socket, response, sizeof(response), 0);
                return 0;
            }
            default: {
                char response[] = "Invalid choice. Please select a valid option.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
        }
    }

    return 0;
}

