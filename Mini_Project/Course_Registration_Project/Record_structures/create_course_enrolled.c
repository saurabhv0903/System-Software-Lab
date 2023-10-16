#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define Course_Enrolled_Path "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/database/course_enrolled.txt"

struct course_enrolled{
    int roll;
    char course_enrolled[4][50];
    int cid;
};

int course_enrolled(){
	
	//int fd = open(Student_Path, O_CREAT | O_RDWR, 0666);
    int fd = open(Course_Enrolled_Path,O_RDWR);
	if(fd==-1){
		perror("File error");
	}

	return fd;
}