#ifndef __DB_H__
#define __DB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CourseSchedule_
{
    char classCode[10];
    char courseCode[10];
    char courseName[30];
    int weekDay;
    int session;    
    int startTime;
    int endTime;
    char week[20];
    char room[10];
};

struct StudentRegistration_
{
    char studentId[10];
    char classCode[10];
};

struct UserAccount_
{
    char studentId[20];
    char password[20];
};

typedef struct CourseSchedule_ CourseSchedule;
typedef struct StudentRegistration_ StudentRegistration;
typedef struct UserAccount_ UserAccount;

void getCourseSchedule(char *fileName);
void getStudentRegistration(char *fileName);
void getUserAccount(char *fileName);

CourseSchedule *courseSchedule;
StudentRegistration *studentRegistration;
UserAccount *userAccount;

int courseTotal;
int registrationTotal;
int userTotal;

#endif
