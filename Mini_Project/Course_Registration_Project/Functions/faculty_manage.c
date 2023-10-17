#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Record_structures/course.h"


#define FACULTY_PATH "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/database/Faculty.txt"
#define PORT 8085
#define BUFFER_SIZE 4096

char send_response[BUFFER_SIZE];
char read_response[BUFFER_SIZE];
char menu2[] = "\n\nEnter the Option:\n1. View Offering courses\n2. Add New Course\n3. Remove course from catalog\n4. Update Course Details\n5. Change password\n6. Logout\n";

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
        if( strcmp(course.id, string_response) == 0){

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
    bzero(send_response, sizeof(send_response));



    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    return 0;
}

int change_password1(char id[], int client_socket){

    char string_response[BUFFER_SIZE];
    int fd_faculty = open(FACULTY_PATH,O_RDWR);
	if(fd_faculty == -1){
		perror("File error");
	}
    else{
        printf("Faculty file opened successfully");
    }
    


    //adding course

    struct Faculty faculty;
    
    //- sizeof(struct), seek cur
    printf("Acquiring record lock on Faculty.txt\n");
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Faculty);
    lock.l_pid = getpid();
    
    fcntl(fd_faculty, F_SETLKW, &lock);
    printf("Lock acquired on Faculty.txt\n");


    while (read(fd_faculty, &faculty, sizeof(struct Faculty)) > 0) {
        // Process the course record
        printf("ID: %s\n", faculty.id);
        printf("Username: %s\n", faculty.username);
        printf("Name: %s\n", faculty.name);
        printf("input ID: %s\n", id);

        printf("\n");

        if( strcmp(id, faculty.id) == 0 ){
            

            strcpy(send_response, "Enter new password: ");
            send(client_socket, send_response, strlen(send_response), 0);

            bzero(read_response, sizeof(read_response));
            recv(client_socket, read_response, sizeof(read_response), 0);

            strcpy(string_response,read_response);
            printf("%s\n", string_response);
            
            if (strchr(read_response, '\n') != NULL) {
                read_response[strlen(read_response) - 1] = '\0';
            }


            strcpy(faculty.password, string_response);
            
            lseek(fd_faculty, -sizeof(struct Faculty), SEEK_CUR);
            write(fd_faculty, &faculty, sizeof(faculty)); 

            printf("\n after change password\nPassowrd: %s\n", faculty.password);

            printf("\n");
            break;
        }


    }
    
   
    
    lock.l_type=F_UNLCK;
	fcntl(fd_faculty,F_SETLKW,&lock);
    
    close(fd_faculty);

    return 0;
}

int update_course(char id[], int client_socket){


    int fd_student = open("course.txt",O_RDWR);
    char string_response[BUFFER_SIZE];
    int check = 0; 
    
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Course);
    lock.l_pid = getpid();

    if (fcntl(fd_student, F_SETLKW, &lock) == -1) {
        perror("Error acquiring file lock");
        close(fd_student);
        return 0;
    }
    struct Course course;



    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }


    strcpy(send_response, "Enter the course id: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);

    while (read(fd_student, &course, sizeof(struct Course)) > 0) {

        printf("\n");
        if( strcmp(string_response, course.course_id) == 0 ){
            
            printf("Before updating\n\nCourse ID: %s\n", course.course_id);
            printf("Course name: %s\n", course.course_name);
            printf("Course credits: %s\n", course.course_credit);
            // printf("Total seats: %d\n", course.total_seats);
            

            printf("\nEntered the main logic for update\n\n");    
            
    
    
            strcpy(send_response, "Enter what you want to update of Course: \n\n1. Update Name\n2. Update Course credits\n");
            send(client_socket, send_response, strlen(send_response), 0);

            bzero(read_response, sizeof(read_response));
            recv(client_socket, read_response, sizeof(read_response), 0);

            strcpy(string_response,read_response);
            printf("%s\n", string_response);

            int client_input = atoi(string_response);
            

            switch (client_input) {
                case 1: {
                    //update name
                    strcpy(send_response, "Enter new name\n");
                    send(client_socket, send_response, strlen(send_response), 0);

                    bzero(read_response, sizeof(read_response));
                    recv(client_socket, read_response, sizeof(read_response), 0);

                    strcpy(string_response,read_response);
                    printf("%s\n", string_response);
                    
                    strcpy(course.course_name, string_response);
                    
                    break;
                }

                case 2: {
                    //update department

                    strcpy(send_response, "Enter new course credits\n");
                    send(client_socket, send_response, strlen(send_response), 0);

                    bzero(read_response, sizeof(read_response));
                    recv(client_socket, read_response, sizeof(read_response), 0);

                    strcpy(string_response,read_response);
                    printf("%s\n", string_response);
                    
                    strcpy(course.course_credit, string_response);
                    break;
                }
            }

            
            lseek(fd_student, -sizeof(struct Course), SEEK_CUR);
            write(fd_student, &course, sizeof(course)); 

            strcpy(send_response, "Course updated\n\n");
            strcat(send_response, menu1);

            send(client_socket, send_response, strlen(send_response), 0);
            
            printf("After updating\n\nCourse ID: %s\n", course.course_id);
            printf("Course name: %s\n", course.course_name);
            printf("Course credits: %s\n", course.course_credit);
            // printf("Total seats: %d\n", course.total_seats);
            
            check = 1;
            break;
        }

    }

    if(check == 0){
        bzero(send_response, sizeof(send_response));
        strcat(send_response, menu1);
        send(client_socket, "Course not found\n\n", strlen("Course not found\n\n"), 0);
    }

    lock.l_type=F_UNLCK;
	fcntl(fd_student,F_SETLKW,&lock);

    return 0;
}

int faculty_manage(char id[], int client_socket){
    char menu[] = "\nFaculty logged in\n\nEnter the Option:\n1. View Offering courses\n2. Add New Course\n3. Remove course from catalog\n4. Update Course Details\n5. Change password\n6. Logout\n";
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
                update_course(id, client_socket);
                break;
            }
            case 5: {
                // Update Details functionality
                // Implement this functionality here, including data storage
                change_password1(id, client_socket);
                char response[] = "password changed.\n\n";
                
                strcat(response, menu2);
                
                send(client_socket, response, sizeof(response), 0);
                
                break;
            }
            
            case 6: {
                // Logout functionality
                // char response[] = "Logged out.\n";
                // send(client_socket, response, sizeof(response), 0);
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

