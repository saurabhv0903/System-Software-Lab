#ifndef YOUR_HEADER_FILE_H
#define YOUR_HEADER_FILE_H


struct Course
{
    char course_id[10];
    char id[10];
    char course_name[50];
    char active[2];
    char dept[50];
    char course_credit[10];
    char total_seats[10];
    char avail_seats[10];
    
};

struct Enroll
{
    char roll[10];
    char course_id[10];
    // char course_name[50]; 

};


#endif
