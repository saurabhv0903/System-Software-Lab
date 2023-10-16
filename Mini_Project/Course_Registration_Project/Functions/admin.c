#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Record_structures/create_student.c"
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Record_structures/create_faculty.c"


#define PORT 8085
#define BUFFER_SIZE 4096

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


int add_student(int client_socket){

    //will create the database Student if not present
    int fd_student = create_student();

    //adding student
    int option;
    struct Student new_student;
    char string_response[20];
    
    
    //set the offset to the record we want to change
    // int offset = (option - 1) * sizeof(struct data);
    lseek(fd_student, 0, SEEK_END);
    
    printf("Acquiring record lock on Student.txt\n");
    
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Student);
    lock.l_pid = getpid();
    
    fcntl(fd_student, F_SETLKW, &lock);
    printf("Lock acquired on Student.txt\n");



    strcpy(send_response, "Enter Username for Student: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_student.username, string_response);


    strcpy(send_response, "Enter password for Student: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_student.password, string_response);



    strcpy(send_response, "Enter name for Student: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_student.name, string_response);



    strcpy(send_response, "Enter roll number for Student: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    new_student.roll = atoi(string_response);



    strcpy(send_response, "Enter activation status for Student: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    new_student.status = atoi(string_response);
     
    write(fd_student, &new_student, sizeof(new_student));    
    
    lock.l_type=F_UNLCK;
	fcntl(fd_student,F_SETLKW,&lock);
    
    close(fd_student);

    return 0;
}


int view_students(int client_socket){

    int fd_student = create_student();
    char string_response[BUFFER_SIZE];
    
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Student);
    lock.l_pid = getpid();

    if (fcntl(fd_student, F_SETLKW, &lock) == -1) {
        perror("Error acquiring file lock");
        close(fd_student);
        return 0;
    }
    struct Student student;


    strcpy(send_response, "Enter the roll of Student: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);

    int client_input = atoi(string_response);


    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }


    while (read(fd_student, &student, sizeof(struct Student)) > 0) {
        // Process the student record
        printf("Roll: %d\n", student.roll);
        printf("Username: %s\n", student.username);
        printf("Name: %s\n", student.name);
        printf("Status: %d\n", student.status);
        // for (int i = 0; i < 4; i++) {
        //     printf("Course Enrolled %d: %s\n", i + 1, student.course_enrolled[i]);
        // }
        printf("\n");
        
        if(client_input == student.roll){
            sprintf(send_response, "Roll: %d\nUsername: %s\nName: %s\nActivation Status: %d\n\nEnter the Option:\n1. Add Student\n2. Add Faculty\n3. View Students\n4. Activate Student\n5. Decativate Student\n6. Update Student Details\n7. View Faculty\n8. Update Faculty\n9. Logout\n", student.roll, student.username, student.name, student.status );

            send(client_socket, send_response, strlen(send_response), 0);
            break;
        }

    }
    lock.l_type=F_UNLCK;
	fcntl(fd_student,F_SETLKW,&lock);
    return 0;
}




int add_faculty(int client_socket){

    //will create the database Student if not present
    int fd_faculty = create_faculty();

    //adding student
    int option;
    struct Faculty new_faculty;
    char string_response[20];
    
    
    //set the offset to the record we want to change
    // int offset = (option - 1) * sizeof(struct data);
    lseek(fd_faculty, 0, SEEK_END);
    
    printf("Acquiring record lock on FAculty.txt\n");
    
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Faculty);
    lock.l_pid = getpid();
    
    fcntl(fd_faculty, F_SETLKW, &lock);
    printf("Lock acquired on Faculty.txt\n");



    strcpy(send_response, "Enter Username for Faculty: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_faculty.username, string_response);


    strcpy(send_response, "Enter password for Faculty: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_faculty.password, string_response);



    strcpy(send_response, "Enter name for Faculty: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_faculty.name, string_response);



    strcpy(send_response, "Enter id for Faculty: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_faculty.id, string_response);



    strcpy(send_response, "Enter department for Faculty: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_faculty.dept, string_response);

    
    strcpy(send_response, "Enter email for Faculty: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_faculty.email, string_response);
     
    write(fd_faculty, &new_faculty, sizeof(new_faculty));    
    
    lock.l_type=F_UNLCK;
	fcntl(fd_faculty,F_SETLKW,&lock);
    
    close(fd_faculty);

    return 0;
}

int view_faculty(int client_socket){

    int fd_faculty = create_faculty();
    char string_response[BUFFER_SIZE];
    
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Faculty);
    lock.l_pid = getpid();

    if (fcntl(fd_faculty, F_SETLKW, &lock) == -1) {
        perror("Error acquiring file lock");
        close(fd_faculty);
        return 0;
    }
    struct Faculty faculty;


    strcpy(send_response, "Enter the id of Faculty: ");
    send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);


    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }


    while (read(fd_faculty, &faculty, sizeof(struct Faculty)) > 0) {
        // Process the faculty record
        printf("ID: %s\n", faculty.id);
        printf("Username: %s\n", faculty.username);
        printf("Name: %s\n", faculty.name);

        printf("\n");
        char client_input[10];
        strcpy(client_input, string_response);
        printf("client input: %s\n", client_input);

        if( strcmp(client_input, faculty.id) == 0){
            printf("faculty found\n");
            sprintf(send_response, "ID: %s\nUsername: %s\nName: %s\n\nEnter the Option:\n1. Add Student\n2. Add Faculty\n3. View Students\n4. Activate Student\n5. Decativate Student\n6. Update Student Details\n7. View Faculty\n8. Update Faculty\n9. Logout\n", faculty.id, faculty.username, faculty.name );

            send(client_socket, send_response, strlen(send_response), 0);
            break;
        }

    }
    lock.l_type=F_UNLCK;
	fcntl(fd_faculty,F_SETLKW,&lock);
    return 0;
}





int admin(int client_socket){
    char menu[] = "\nAdmin logged in\n\nEnter the Option:\n1. Add Student\n2. Add Faculty\n3. Activate Student\n4. Decativate Student\n5. Update Student Details\n6. Update Faculty Details\n7. View Student\n8. View Faculty\n9. Logout\n";
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
                char response[] = "View Student Details.\n";
                view_students(client_socket);
                // send(client_socket, response, sizeof(response), 0);
                break;
            }
            case 8: {
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

