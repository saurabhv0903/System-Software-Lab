
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define Faculty_Path "/home/saurabh/MTech/SS/Handson/Mini_Project/Course_Registration_Project/database/Faculty.txt"

struct Faculty{
    char id[10];
    char username[50];
    char password[50];
    char name[50];
    char dept[50];
    char email[50];
};

int create_faculty(){
	
	//int fd = open(Student_Path, O_CREAT | O_RDWR, 0666);
    int fd = open(Faculty_Path,O_RDWR);
	if(fd==-1){
		perror("File error");
	}

	return fd;
}
