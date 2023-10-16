#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
// #include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Record_structures/create_faculty.c"
// #include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Record_structures/create_faculty.c"
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Record_structures/course.h"

#define PORT 8085
#define BUFFER_SIZE 4096

char send_response[BUFFER_SIZE];
char read_response[BUFFER_SIZE];

/*
struct Course{
    char username[50];
    char password[50];
    char name[50];
    int id;
    int status;
    char course_enided[4][30];
};

struct Course{
    int id;
    char username[50];
    char password[50];
    char name[50];
    int status;
    char course_offered[4][30];
};

*/

int add_course(char id[], int client_socket){

    int fd_course = open("course.txt",O_RDWR);
	if(fd_course == -1){
		perror("File error");
	}
    else{
        printf("course file opened successfully");
    }
    

    //adding course
    int option;
    struct Course course;
    char string_response[20];
    
    
    //set the offset to the record we want to change
    lseek(fd_course, 0, SEEK_END);
    
    printf("Acquiring record lock on Course.txt\n");
    
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Course);
    lock.l_pid = getpid();
    
    fcntl(fd_course, F_SETLKW, &lock);
    printf("Lock acquired on Course.txt\n");



    strcpy(send_response, "Enter course id for Course: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(course.course_id, string_response);


    strcpy(send_response, "Enter professor id for Course: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(course.id, string_response);



    strcpy(send_response, "Enter name for Course: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(course.course_name, string_response);

    strcpy(course.active, "1");

    strcpy(send_response, "Enter department for Course: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(course.dept, string_response);

    
    strcpy(send_response, "Enter credits for Course: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(course.course_credit, string_response);



    strcpy(send_response, "Enter total seats for Course: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(course.total_seats, string_response);



    strcpy(send_response, "Enter total available seats for Course: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(course.avail_seats, string_response);



     
    write(fd_course, &course, sizeof(course));    
    
    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    
    close(fd_course);
    return 0;
}


int view_offering_course(char id[], int client_socket){

    int fd_course = open("course.txt",O_RDWR);
	if(fd_course == -1){
		perror("File error");
	}
    
    char string_response[BUFFER_SIZE];
    char course_entries[BUFFER_SIZE];
    char send_response[BUFFER_SIZE];

    

    strcpy(send_response, "Enter professor id: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }



    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Course);
    lock.l_pid = getpid();

    if (fcntl(fd_course, F_SETLKW, &lock) == -1) {
        perror("Error acquiring file lock");
        close(fd_course);
        return 0;
    }
    struct Course course;


    while (read(fd_course, &course, sizeof(struct Course)) > 0 ) {
        if( strcpy(course.id, string_response) ){

        // Process the course record
        printf("Course id: %s\n", course.course_id);
        printf("Username: %s\n", course.course_name);
        printf("Name: %s\n", course.dept);
        printf("Active: %s\n", course.active);

        printf("\n");
        
        sprintf(course_entries, "Course id: %s\nCourse name: %s\nOffered by department: %s\nTotal seats: %s\n\n", course.course_id, course.course_name, course.dept, course.total_seats );
        strcat(send_response, course_entries);
        }   
    }
    strcat(send_response, "\nEnter the Option:\n1. View Offering courses\n2. Add New Course\n3. Remove course from catalog\n4. Update Course Details\n5. Change password\n9. Logout\n"); 

    send(client_socket, send_response, strlen(send_response), 0);   


    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    return 0;
}




int faculty_manage(char id[], int client_socket){
    char menu[] = "\nFaculty logged in\n\nEnter the Option:\n1. View Offering courses\n2. Add New Course\n3. Remove course from catalog\n4. Update Course Details\n5. Change password\n9. Logout\n";
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

                view_offering_course(id, client_socket);
                break;
            }
            case 2: {
                // Add Course functionality
                // Implement this functionality here, including data storage
                add_course(id, client_socket);
                char response[] = "Added Course.\n\nEnter the Option:\n1. View Offering courses\n2. Add New Course\n3. Remove course from catalog\n4. Update Course Details\n5. Change password\n6. Logout\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 3: {
                // Activate Course functionality
                // Implement this functionality here, including data storage
                char response[] = "Activated Course.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 4: {
                // Deactivate Course functionality
                // Implement this functionality here, including data storage
                char response[] = "Deactivated Course.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 5: {
                // Update Details functionality
                // Implement this functionality here, including data storage
                char response[] = "Updated Course Details.\n";
                
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 6: {
                // Update Details functionality
                // Implement this functionality here, including data storage
                char response[] = "Updated Course Details.\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 7: {
                // Logout functionality
                char response[] = "View Course Details.\n";
                view_faculty(client_socket);
                // send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 8: {
                // Logout functionality
                char response[] = "View Course Details.\n";
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

