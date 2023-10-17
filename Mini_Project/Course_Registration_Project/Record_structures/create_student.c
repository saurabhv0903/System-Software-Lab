
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define Student_Path "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/database/Student.txt"

struct Student{
    int roll;
    char username[50];
    char password[50];
    char name[50];
    int status;
    char email[50];
    int enrolled;                   //add student, view student
    // char course_enrolled[4][30];
};

int create_student(){
	
	//int fd = open(Student_Path, O_CREAT | O_RDWR, 0666);
    int fd = open(Student_Path,O_RDWR);
	if(fd==-1){
		perror("File error");
	}

	return fd;
}


/*
#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int rollNumber;
    char courseEnrollments[10][50];
};

int main() {
    struct Student student1;

    printf("Enter Student Name: ");
    fgets(student1.name, sizeof(student1.name), stdin);
    student1.name[strcspn(student1.name, "\n")] = '\0'; // Remove newline character if present

    printf("Enter Roll Number: ");
    scanf("%d", &student1.rollNumber);
    getchar(); // Consume newline character left in the buffer

    printf("Enter Course Enrollments (one per line, up to 10 courses, press Enter to finish):\n");
    for (int i = 0; i < 10; i++) {
        fgets(student1.courseEnrollments[i], sizeof(student1.courseEnrollments[i]), stdin);
        student1.courseEnrollments[i][strcspn(student1.courseEnrollments[i], "\n")] = '\0';
        if (strlen(student1.courseEnrollments[i]) == 0) {
            break;
        }
    }

    FILE *file = fopen("student_data.txt", "a");
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    fprintf(file, "Student Name: %s\n", student1.name);
    fprintf(file, "Roll Number: %d\n", student1.rollNumber);
    fprintf(file, "Enrolled Courses:\n");

    for (int i = 0; i < 10; i++) {
        if (strlen(student1.courseEnrollments[i]) == 0) {
            break;
        }
        fprintf(file, "%d. %s\n", i + 1, student1.courseEnrollments[i]);
    }

    fprintf(file, "\n");
    fclose(file);

    printf("Data has been written to student_data.txt\n");

    return 0;
}

*/