
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define Faculty_Path "/home/saurabh/MTech/SS/Handson/Project/Course_Registration_Project/database/Faculty.txt"

struct Faculty{
    int id;
    char username[50];
    char password[50];
    char name[50];
    int status;
    char course_offered[4][30];
};

int create_faculty(){
	
	//int fd = open(Student_Path, O_CREAT | O_RDWR, 0666);
    int fd = open(Faculty_Path,O_RDWR);
	if(fd==-1){
		perror("File error");
	}

	return fd;
}
