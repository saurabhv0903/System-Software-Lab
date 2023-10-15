#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Functions/student_manage.c"

#define PORT 8085
#define BUFFER_SIZE 1024


int student_login(int client_socket){

    char buffer[BUFFER_SIZE];
    char write_buffer[BUFFER_SIZE];

    char student_username1[20] ;
    char student_password1[20] ;
    char menu[300];
    int wrong_credentials = 0;

    while(1){
        //student sign in for username
        if(wrong_credentials == 0){
            strcpy(menu, "\nYou selected student\nSign in for student: Enter Username: ");
            send(client_socket, menu, strlen(menu), 0);
        }
        else{
            strcpy(menu, "\n\nYour have entered wrong credentials\n\nSign in for student: Enter Username: ");
            send(client_socket, menu, strlen(menu), 0);
        }

        bzero(buffer, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);

        strcpy(student_username1,buffer);
        printf("%s\n", student_username1);
        
        if (strchr(buffer, '\n') != NULL) {
            buffer[strlen(buffer) - 1] = '\0';
        }

        //student sign in for password
        bzero(menu, sizeof(menu));
        strcpy(menu, "Password: ");
        send(client_socket, menu, strlen(menu), 0);

        bzero(buffer, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);

        if (strchr(buffer, '\n') != NULL) {
            buffer[strlen(buffer) - 1] = '\0';
        }

        strcpy(student_password1, buffer);
        printf("%s\n", student_password1);



        int fd_student = create_student();
        char string_response[BUFFER_SIZE];
        
        struct flock lock;
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = sizeof(struct Student);
        lock.l_pid = getpid();

        if (fcntl(fd_student, F_SETLK, &lock) == -1) {
            perror("Error acquiring file lock");
            close(fd_student);
            return 0;
        }
        struct Student student;



        while (read(fd_student, &student, sizeof(struct Student)) > 0) {

            if (strcmp(student_username1, student.username) == 0 && strcmp(student_password1, student.password) == 0) {
                
                // Process the student record
                printf("Roll: %d\n", student.roll);
                printf("Username: %s\n", student.username);
                printf("Name: %s\n", student.name);
                printf("Status: %d\n", student.status);
                // for (int i = 0; i < 4; i++) {
                //     printf("Course Enrolled %d: %s\n", i + 1, student.course_enrolled[i]);
                // }
                printf("\n");
                
                wrong_credentials = 0;
                student_manage(client_socket);
                break;
            }
            else{
                wrong_credentials = 1;
                break;
            }

        }

        lock.l_type=F_UNLCK;
        fcntl(fd_student,F_SETLK,&lock);
    }


    close(client_socket);
    return 0;
}
