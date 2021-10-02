#include "controller.h"
#include "db.h"

void menu()
{
    int choose;
    do
    {
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Choose a number: ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            login();
            break;
        case 2:
            exit(0);
            break;
        default:
            printf("Invalid input. Please retype !\n");
            choose = 2;
            break;
        }
    } while (choose == 1 || choose == 2);
}

void login()
{
    char stID[10];
    char pwd[10];
    int loginSuccessfull = 0;
    printf("Enter student ID: ");
    scanf("%s", stID);
    printf("Enter password: ");
    scanf("%s", pwd);
    int i = 0;
    while (i < userTotal)
    {
        if (!strcmp(userAccount[i].studentId, stID) && !strcmp(userAccount[i].password, pwd))
            loginSuccessfull = 1;
        i++;
    };

    if (loginSuccessfull)
    {
        schedule(stID);
    }
    else
        printf("Invalid account !\n");
}

void schedule(char *stdID)
{
    int choose;
    do
    {
        printf("1. View the schedule by day or all day\n");
        printf("2. Exit\n");
        printf("Choose a number: ");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            printSchedule(stdID);
            break;
        case 2:
            exit(0);
            break;
        default:
            printf("Invalid input. Please retype !\n");
            choose = 2;
            break;
        }
    } while (choose == 1 || choose == 2);
}

void printSchedule(char *stdID)
{
    int day;
    printf("Enter a day (1 to view all): ");
    scanf("%d", &day);
    int i = 0, j = 0, k = 0;
    char classCode[20][20];
    while (i < registrationTotal)
    {
        if (!strcmp(studentRegistration[i].studentId, stdID))
        {
            strcpy(classCode[j], studentRegistration[i].classCode);
            j++;
        }
        i++;
    }
    printf("%-10s| %-30s| %-15s| %-15s| %-8s| %-20s| %-10s\n", "Code", "Course", "Week Day", "AM/PM", "Period", "Week", "Room");
    i = 0;
    while (i < courseTotal)
    {
        k = 0;
        while (k < j)
        {
            if (day != 1){
                if (!strcmp(courseSchedule[i].classCode, classCode[k]) && courseSchedule[i].weekDay == day)
                    printf("%-10s|%-31s| %-15s| %-15s| %d-%-6d| %-20s| %-10s\n", courseSchedule[i].courseCode, courseSchedule[i].courseName, convertWeekDayToString(courseSchedule[i].weekDay), convertSessionToString(courseSchedule[i].session), courseSchedule[i].startTime, courseSchedule[i].endTime, courseSchedule[i].week, courseSchedule[i].room);
            }
            else {
                if (!strcmp(courseSchedule[i].classCode, classCode[k]))
                    printf("%-10s|%-31s| %-15s| %-15s| %d-%-6d| %-20s| %-10s\n", courseSchedule[i].courseCode, courseSchedule[i].courseName, convertWeekDayToString(courseSchedule[i].weekDay), convertSessionToString(courseSchedule[i].session), courseSchedule[i].startTime, courseSchedule[i].endTime, courseSchedule[i].week, courseSchedule[i].room);
            }
            k++;
        }
        i++;
    }
}

char *convertWeekDayToString(int weekDay)
{
    switch (weekDay)
    {
    case 2:
        return "Monday";
        break;
    case 3:
        return "Tuesday";
        break;
    case 4:
        return "Wednesday";
        break;
    case 5:
        return "Thursday";
        break;
    case 6:
        return "Friday";
        break;
    case 7:
        return "Saturday";
        break;
    default:
        return NULL;
        break;
    }
}

char *convertSessionToString(int session)
{
    switch (session)
    {
    case 1:
        return "Morning";
        break;
    case 2:
        return "Afternoon";
        break;
    default:
        return NULL;
        break;
    }
}
