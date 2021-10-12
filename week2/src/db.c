#include "db.h"

void getCourseSchedule(char *fileName)
{
    char c;
    courseTotal = 0;
    courseSchedule = (CourseSchedule *)calloc(10, sizeof(CourseSchedule));

    FILE *courseScheduleFile = fopen("courseSchedule.txt", "r");
    if (courseScheduleFile == NULL)
    {
        printf("Can\'t read courseSchedule file!\n");
        return;
    }
    while (fscanf(courseScheduleFile, "%s", courseSchedule[courseTotal].classCode) > 0)
    {
        fscanf(courseScheduleFile, "%s", courseSchedule[courseTotal].courseCode);
        fscanf(courseScheduleFile, "%[^0-9]s", courseSchedule[courseTotal].courseName);
        fscanf(courseScheduleFile, "%c", &c);
        courseSchedule[courseTotal].weekDay = c - '0';
        fscanf(courseScheduleFile, "%c", &c);
        courseSchedule[courseTotal].session = c - '0';
        fscanf(courseScheduleFile, "%c", &c);
        courseSchedule[courseTotal].startTime = c - '0';
        fscanf(courseScheduleFile, "%c%c%c", &c, &c, &c);
        fscanf(courseScheduleFile, "%c", &c);
        courseSchedule[courseTotal].endTime = c - '0';
        fscanf(courseScheduleFile, "%c", &c);
        fscanf(courseScheduleFile, "%[^A-Z]s", courseSchedule[courseTotal].week);
        courseSchedule[courseTotal].week[strlen(courseSchedule[courseTotal].week) - 1] = '\0';
        fscanf(courseScheduleFile, "%[^;]s", courseSchedule[courseTotal].room);
        fscanf(courseScheduleFile, "%c", &c);
        courseTotal++;
    }
    fclose(courseScheduleFile);
};

void getStudentRegistration(char *fileName)
{
    registrationTotal = 0;
    studentRegistration = (StudentRegistration *)calloc(10, sizeof(StudentRegistration));

    FILE *studentRegistrationFile = fopen("studentRegistration.txt", "r");
    if (studentRegistrationFile == NULL)
    {
        printf("Can\'t read studentRegistration file!\n");
        return;
    }

    while (fscanf(studentRegistrationFile, "%s", studentRegistration[registrationTotal].studentId) > 0)
    {
        fscanf(studentRegistrationFile, "%s", studentRegistration[registrationTotal].classCode);
        registrationTotal++;
    }
    
    fclose(studentRegistrationFile);
};

void getUserAccount(char *fileName)
{
    userTotal = 0;
    userAccount = (UserAccount *)malloc(10*sizeof(userAccount));

    FILE *userAccountFile = fopen("userAccount.txt", "r");
    if (userAccountFile == NULL)
    {
        printf("Can\'t read userAccount file!\n");
        return;
    }

    while (fscanf(userAccountFile, "%s", userAccount[userTotal].studentId) > 0)
    {
        fscanf(userAccountFile, "%s", userAccount[userTotal].password);
        userTotal++;
    }
    fclose(userAccountFile);
};