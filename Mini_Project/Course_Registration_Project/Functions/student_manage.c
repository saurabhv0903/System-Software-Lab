#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
// #include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Record_structures/create_student.c"
// #include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Record_structures/create_faculty.c"

#define PORT 8085
#define BUFFER_SIZE 4096

char send_response[BUFFER_SIZE];
char read_response[BUFFER_SIZE];
char menu[] = "\nStudent logged in\n\nEnter the Option:\n1. View all courses\n2. Enroll new course\n3. Drop course\n4. View Enrolled details\n5. Chnage password\n6. Logout\n";
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

int view_offering_course(struct Student loggedin_student, int client_socket){

    int fd_course = open("course.txt",O_RDWR);
	if(fd_course == -1){
		perror("File error");
	}
    
    char string_response[BUFFER_SIZE];
    char course_entries[BUFFER_SIZE];
    
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


    while (read(fd_course, &course, sizeof(struct Course)) > 0) {
        // Process the course record
        printf("Course id: %s\n", course.course_id);
        printf("Username: %s\n", course.course_name);
        printf("Name: %s\n", course.dept);
        printf("Active: %s\n", course.active);

        printf("\n");
        
        sprintf(course_entries, "Course id: %s\nCourse name: %s\nOffered by department: %s\nTotal seats: %s\n\n", course.course_id, course.course_name, course.dept, course.total_seats );
        strcat(send_response, course_entries);   
    }
    strcat(send_response, menu); 

    send(client_socket, send_response, strlen(send_response), 0);   


    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    return 0;
}


int enroll_course(struct Student loggedin_student, int client_socket){

    return 0;
}



int student_manage(struct Student loggedin_student, int client_socket){
    
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

                view_all_courses(loggedin_student, client_socket);
                
                break;
            }
            case 2: {

                enroll_course(loggedin_student, client_socket);
                char response[] = "Course Enrolled \n\n1. View all courses\n2. Enroll new course\n3. Drop course\n4. View Enrolled details\n5. Chnage password\n6. Logout\n";
                send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 3: {

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
                break;
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

