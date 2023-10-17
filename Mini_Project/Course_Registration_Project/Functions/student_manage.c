#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
// #include "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/Record_structures/create_student.c"
#include "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/Record_structures/course.h"
#define STUDENT_PATH "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/database/Student.txt"

#define PORT 8085
#define BUFFER_SIZE 4096

char send_response[BUFFER_SIZE];
char read_response[BUFFER_SIZE];
char menu[] = "\n\nEnter the Option:\n1. View all courses\n2. Enroll new course\n3. Drop course\n4. View Enrolled details\n5. Change password\n6. Logout\n";
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

int view_all_courses(struct Student loggedin_student, int client_socket){

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

    sprintf(course_entries, "Available courses:\n\n");

    while (read(fd_course, &course, sizeof(struct Course)) > 0) {
        // Process the course record
        printf("Course id: %s\n", course.course_id);
        printf("Username: %s\n", course.course_name);
        printf("Name: %s\n", course.dept);
        printf("Active: %s\n", course.active);

        printf("\n");
        
        sprintf(course_entries, "Course id: %s\nCourse name: %s\nOffered by department: %s\nTotal seats: %s\nAvailable seats: %s\n\n", course.course_id, course.course_name, course.dept, course.total_seats, course.avail_seats );
        strcat(send_response, course_entries);   
    }
    strcat(send_response, menu); 

    send(client_socket, send_response, strlen(send_response), 0);   
    bzero(send_response, sizeof(send_response));


    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    return 0;
}

int enroll_course(struct Student loggedin_student, int client_socket){
    
    
    int fd_student = open("enrolled_course.txt",O_RDWR);

    int option;
    struct Enroll new_enroll;
    char string_response[20];
    
    

    lseek(fd_student, 0, SEEK_END);
    
    printf("Acquiring record lock on enrolled_course.txt\n");
    
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Enroll);
    lock.l_pid = getpid();
    
    fcntl(fd_student, F_SETLKW, &lock);
    printf("Lock acquired on enrolled_course.txt\n");



    //displaying all the courses
    int fd_course = open("course.txt",O_RDWR);
	if(fd_course == -1){
		perror("File error");
	}
    
    char course_entries[BUFFER_SIZE];
    
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

    sprintf(course_entries, "Available courses:\n\n");

    while (read(fd_course, &course, sizeof(struct Course)) > 0) {
        // Process the course record
        printf("Course id: %s\n", course.course_id);
        printf("Username: %s\n", course.course_name);
        printf("Name: %s\n", course.dept);
        printf("Active: %s\n", course.active);

        printf("\n");
        
        sprintf(course_entries, "Course id: %s\nCourse name: %s\nOffered by department: %s\nTotal seats: %s\nAvailable seats: %s\n\n", course.course_id, course.course_name, course.dept, course.total_seats, course.avail_seats );
        strcat(send_response, course_entries);   
    }
    
    strcat(send_response, "Enter course id to register: ");
    send(client_socket, send_response, strlen(send_response), 0);   
    bzero(send_response, sizeof(send_response));


    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    close(fd_course);




    //enroll course
    // strcpy(send_response, "Enter course id to register: ");
    // send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_enroll.course_id, string_response);

    sprintf(new_enroll.roll, "%d", loggedin_student.roll);

     
    write(fd_student, &new_enroll, sizeof(new_enroll));   
 
    
    lock.l_type=F_UNLCK;
	fcntl(fd_student,F_SETLKW,&lock);
    
    close(fd_student);

    



    //decrease count of course 
    fd_course = open("course.txt",O_RDWR);
	if(fd_course == -1){
		perror("File error");
	}
    else{
        printf("course file opened successfully");
    }
    

    //- sizeof(struct), seek cur
    printf("Acquiring record lock on Course.txt\n");
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Course);
    lock.l_pid = getpid();
    
    fcntl(fd_course, F_SETLKW, &lock);
    printf("Lock acquired on Course.txt\n");
    lseek(fd_course, 0, SEEK_SET);

    while (read(fd_course, &course, sizeof(struct Course)) > 0) {
        // Process the course record
        printf("Course id: %s\n", course.course_id);
        printf("Username: %s\n", course.course_name);
        printf("Name: %s\n", course.dept);
        printf("Active: %s\n", course.active);
        printf("total available seats: %s\n", course.avail_seats);

        printf("\n");

        if( strcmp( new_enroll.course_id, course.course_id ) == 0 ){
            int temp = atoi(course.avail_seats) - 1;
            sprintf(course.avail_seats, "%d", temp);
            
            lseek(fd_course, -sizeof(struct Course), SEEK_CUR);
            write(fd_course, &course, sizeof(course)); 

            printf("\n after enrollment\ntotal available seats: %s\n", course.avail_seats);

            printf("\n");
            break;
        }


    }
    
   
    
    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    
    close(fd_course);





    //update student 
    int fd_student1 = create_student();
    
    
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Student);
    lock.l_pid = getpid();

    if (fcntl(fd_student1, F_SETLKW, &lock) == -1) {
        perror("Error acquiring file lock");
        close(fd_student1);
        return 0;
    }
    struct Student student;
    lseek(fd_student, 0, SEEK_SET);


    while (read(fd_student1, &student, sizeof(struct Student)) > 0) {

        printf("\n");
        if(loggedin_student.roll == student.roll){
            
            printf("Before updating\n\nRoll: %d\n", student.roll);
            printf("Username: %s\n", student.username);
            printf("Enrolled course: %d\n", student.enrolled);
            printf("Status: %d\n", student.status);
            

            printf("\nEntered the main logic for 3rd file\n\n");    
            
            student.enrolled = student.enrolled + 1;
    
            
            
            lseek(fd_student, -sizeof(struct Student), SEEK_CUR);
            write(fd_student, &student, sizeof(student)); 

            strcpy(send_response, "Enrolled course\n\n");
            strcat(send_response, menu);
            send(client_socket, send_response, strlen(send_response), 0);
            
            printf("After updating\n\nRoll: %d\n", student.roll);
            printf("Username: %s\n", student.username);
            printf("Enrolled course: %d\n", student.enrolled);
            printf("Status: %d\n", student.status);
            
            break;
        }

    }

    lock.l_type=F_UNLCK;
    fcntl(fd_student,F_SETLKW,&lock);
    close(fd_student1);


    //end

    return 0;
}

int enrolled_course(struct Student loggedin_student, int client_socket){

    int fd_course = open("enrolled_course.txt",O_RDWR);
	if(fd_course == -1){
		perror("File error");
	}
    
    char string_response[BUFFER_SIZE];
    char course_entries[BUFFER_SIZE];
    
    struct flock lock;
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Enroll);
    lock.l_pid = getpid();

    if (fcntl(fd_course, F_SETLKW, &lock) == -1) {
        perror("Error acquiring file lock");
        close(fd_course);
        return 0;
    }
    struct Enroll enroll;

    sprintf(course_entries, "Enrolled courses:\n\n");

    while (read(fd_course, &enroll, sizeof(struct Enroll)) > 0) {
        if( strcmp(enroll.course_id, "0") !=0 && loggedin_student.roll == atoi(enroll.roll) ){
            // Process the enroll record
            printf("Student roll: %s\n", enroll.roll);
            printf("Course id: %s\n", enroll.course_id);

            printf("\n");
            
            sprintf(course_entries, "Student roll: %s\nCourse id: %s\n\n", enroll.roll, enroll.course_id);
            strcat(send_response, course_entries);   
        }
    }
    strcat(send_response, menu); 

    send(client_socket, send_response, strlen(send_response), 0);   
    bzero(send_response, sizeof(send_response));


    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    return 0;   
}

int drop_course(struct Student loggedin_student, int client_socket){
    
    
    int fd_student = open("enrolled_course.txt",O_RDWR);

    //adding student
    int option;
    struct Enroll new_enroll;
    struct Enroll enroll;
    char string_response[20];
    char course_entries[BUFFER_SIZE];
    
    
    //set the offset to the record we want to change
    // int offset = (option - 1) * sizeof(struct data);
    lseek(fd_student, 0, SEEK_END);
    
    printf("Acquiring record lock on enrolled_course.txt\n");
    
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Enroll);
    lock.l_pid = getpid();
    
    fcntl(fd_student, F_SETLKW, &lock);
    printf("Lock acquired on enrolled_course.txt\n");


    //view enrolled course
    
    sprintf(course_entries, "Enrolled courses:\n\n");

    while (read(fd_student, &enroll, sizeof(struct Enroll)) > 0) {
        if( strcmp(enroll.course_id, "0") !=0 && loggedin_student.roll == atoi(enroll.roll) ){
            // Process the enroll record
            printf("Student roll: %s\n", enroll.roll);
            printf("Course id: %s\n", enroll.course_id);

            printf("\n");
            
            sprintf(course_entries, "Student roll: %s\nCourse id: %s\n\n", enroll.roll, enroll.course_id);
            strcat(send_response, course_entries);   
        }
    }
    strcat(send_response, "Enter course id to drop: "); 
    send(client_socket, send_response, strlen(send_response), 0);   
    bzero(send_response, sizeof(send_response));


    lock.l_type=F_UNLCK;
	fcntl(fd_student,F_SETLKW,&lock);




    //drop course
    
    // send(client_socket, send_response, strlen(send_response), 0);

    bzero(read_response, sizeof(read_response));
    recv(client_socket, read_response, sizeof(read_response), 0);

    strcpy(string_response,read_response);
    printf("%s\n", string_response);
    
    if (strchr(read_response, '\n') != NULL) {
        read_response[strlen(read_response) - 1] = '\0';
    }

    strcpy(new_enroll.course_id, string_response);

    sprintf(new_enroll.roll, "%d", loggedin_student.roll);

    lseek(fd_student, 0, SEEK_SET);

    while (read(fd_student, &enroll, sizeof(struct Enroll)) > 0) {
        // Process the course record
        
        printf("Student roll: %s\n", enroll.roll);
        printf("course id: %s\n", enroll.course_id);

        printf("\n");

        if( strcmp(new_enroll.course_id, enroll.course_id) == 0 && loggedin_student.roll == atoi(enroll.roll) ){
            
            printf("Entered the main logic for drop\n");    
            strcpy(new_enroll.course_id, "0");
            
            lseek(fd_student, -sizeof(struct Enroll), SEEK_CUR);
            write(fd_student, &new_enroll, sizeof(new_enroll)); 


            printf("course dropped\n");
            break;
        }


    }


    
    lock.l_type=F_UNLCK;
	fcntl(fd_student,F_SETLKW,&lock);
    
    close(fd_student);

    



    //decrease count of course 
    int fd_course = open("course.txt",O_RDWR);
	if(fd_course == -1){
		perror("File error");
	}
    else{
        printf("course file opened successfully");
    }
    

    //adding course

    struct Course course;
    
    //- sizeof(struct), seek cur
    printf("Acquiring record lock on Course.txt\n");
    
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Course);
    lock.l_pid = getpid();
    
    fcntl(fd_course, F_SETLKW, &lock);
    printf("Lock acquired on Course.txt\n");


    while (read(fd_course, &course, sizeof(struct Course)) > 0) {
        // Process the course record
        printf("Course id: %s\n", course.course_id);
        printf("Username: %s\n", course.course_name);
        printf("Name: %s\n", course.dept);
        printf("Active: %s\n", course.active);
        printf("total available seats: %s\n", course.avail_seats);

        printf("\n");

        if( strcmp(new_enroll.course_id, course.course_id) == 0 ){
            int temp = atoi(course.avail_seats) + 1;
            sprintf(course.avail_seats, "%d", temp);
            
            lseek(fd_course, -sizeof(struct Course), SEEK_CUR);
            write(fd_course, &course, sizeof(course)); 

            printf("\n after drop\ntotal available seats: %s\n", course.avail_seats);

            printf("\n");
            break;
        }


    }
    
   
    
    lock.l_type=F_UNLCK;
	fcntl(fd_course,F_SETLKW,&lock);
    
    close(fd_course);



    //update student

    int fd_student1 = create_student();
    
    lock.l_type = F_RDLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Student);
    lock.l_pid = getpid();

    if (fcntl(fd_student1, F_SETLKW, &lock) == -1) {
        perror("Error acquiring file lock");
        close(fd_student1);
        return 0;
    }
    struct Student student;


    while (read(fd_student1, &student, sizeof(struct Student)) > 0) {

        printf("\n");
        if(loggedin_student.roll == student.roll){
            
            printf("Before updating\n\nRoll: %d\n", student.roll);
            printf("Username: %s\n", student.username);
            printf("Enrolled course: %d\n", student.enrolled);
            printf("Status: %d\n", student.status);
            

            printf("\nEntered the main logic for 3rd file\n\n");    
            
            student.enrolled = student.enrolled + 1;
    
            
            
            lseek(fd_student, -sizeof(struct Student), SEEK_CUR);
            write(fd_student, &student, sizeof(student)); 

            strcpy(send_response, "Course dropped\n\n");
            strcat(send_response, menu);

            send(client_socket, send_response, strlen(send_response), 0);
            
            printf("After updating\n\nRoll: %d\n", student.roll);
            printf("Username: %s\n", student.username);
            printf("Enrolled course: %d\n", student.enrolled);
            printf("Status: %d\n", student.status);
            
            break;
        }

    }

    lock.l_type=F_UNLCK;
    fcntl(fd_student1,F_SETLKW,&lock);
    close(fd_student1);

        //end

    return 0;
}

int change_password(struct Student loggedin_student, int client_socket){

    char string_response[BUFFER_SIZE];
    int fd_student = open(STUDENT_PATH,O_RDWR);
	if(fd_student == -1){
		perror("File error");
	}
    else{
        printf("Student file opened successfully");
    }
    

    //adding course

    struct Student student;
    
    //- sizeof(struct), seek cur
    printf("Acquiring record lock on Student.txt\n");
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_END;
    lock.l_start = 0;
    lock.l_len = sizeof(struct Student);
    lock.l_pid = getpid();
    
    fcntl(fd_student, F_SETLKW, &lock);
    printf("Lock acquired on Student.txt\n");


    while (read(fd_student, &student, sizeof(struct Student)) > 0) {
        // Process the course record
        printf("Course id: %d\n", student.roll);
        printf("Username: %s\n", student.username);
        printf("Name: %s\n", student.name);


        printf("\n");

        if( loggedin_student.roll == student.roll ){
            

            strcpy(send_response, "Enter new password: ");
            send(client_socket, send_response, strlen(send_response), 0);

            bzero(read_response, sizeof(read_response));
            recv(client_socket, read_response, sizeof(read_response), 0);

            strcpy(string_response,read_response);
            printf("%s\n", string_response);
            
            if (strchr(read_response, '\n') != NULL) {
                read_response[strlen(read_response) - 1] = '\0';
            }


            strcpy(student.password, string_response);
            
            lseek(fd_student, -sizeof(struct Student), SEEK_CUR);
            write(fd_student, &student, sizeof(student)); 

            printf("\n after change password\nPassowrd: %s\n", student.password);

            printf("\n");
            break;
        }


    }
    
   
    
    lock.l_type=F_UNLCK;
	fcntl(fd_student,F_SETLKW,&lock);
    
    close(fd_student);

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
                //send handled
                break;
            }
            case 3: {

                drop_course(loggedin_student, client_socket);
                //send handled

                break;
            }
            case 4: {
                enrolled_course(loggedin_student, client_socket);
                //send handled
                break;
            }
            case 5: {
                change_password(loggedin_student, client_socket);
                char response[] = "Updated Student Details.\n";
                strcat(response, menu);
                send(client_socket, response, sizeof(response), 0);
                //send handled
                break;
            }
            
            case 6: {
                // Logout functionality
                // char response[] = "Logged out.\n";
                // send(client_socket, response, sizeof(response), 0);
                return 0;
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

