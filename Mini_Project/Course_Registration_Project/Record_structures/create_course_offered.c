#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define Course_Offered_Path "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/database/course_offered.txt"

struct course_offered{
    int id;
    char course_offered[4][50];
    int cid;
};

int course_offered(){
	
	//int fd = open(Student_Path, O_CREAT | O_RDWR, 0666);
    int fd = open(Course_Offered_Path,O_RDWR);
	if(fd==-1){
		perror("File error");
	}

	return fd;
}