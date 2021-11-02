#include "controller.h"
#include "db.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char *sendToClient(char *buf)
{
    char *recvline = malloc(sizeof(char *) * MAXLINE);
    if (send(connfd, buf, MAXLINE, 0) < 0)
    {
        perror("Read error");
        exit(1);
    }
    if (recv(connfd, recvline, MAXLINE, 0) < 0)
    {
        perror("Read error");
        exit(1);
    }
    recvline[strlen(recvline) - 1] = '\0';
    return recvline;
}

void menu()
{
    int choose;
    do
    {
        strcpy(buf, "1. Login\n2. Exit\nChoose a number: ");
        choose = atoi(sendToClient(buf));
        printf("Choose %d\n", choose);
        switch (choose)
        {
        case 1:
            login();
            break;
        case 2:
            break;
        default:
            printf("%s\n", "Error");
            strcpy(buf, "Invalid input. Please retype !\n");
            sendToClient(buf);
            break;
        }
        if (choose == 2)
            break;
    } while (choose == 1 || choose == 2);
}

void login()
{
    char *stID = malloc(sizeof(char *) * MAXLINE);
    char *pwd = malloc(sizeof(char *) * MAXLINE);
    int loginSuccessfull = 0;
    strcpy(buf, "Enter student ID: ");
    strcpy(stID, sendToClient(buf));
    strcpy(buf, "Enter password: ");
    strcpy(pwd, sendToClient(buf));
    printf("Student %s\n", stID);
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
    {
        printf("%s\n", "Error");
        strcpy(buf, "Invalid account !\n");
        sendToClient(buf);
    }
}

void schedule(char *stdID)
{
    int choose;
    do
    {
        strcpy(buf, "1. View the schedule by day or all day\n2. Back\nChoose a number: ");
        choose = atoi(sendToClient(buf));
        printf("Choose %d\n", choose);
        switch (choose)
        {
        case 1:
            printSchedule(stdID);
            break;
        case 2:
            break;
        default:
            strcpy(buf, "Invalid input. Please retype !\n");
            sendToClient(buf);
            break;
        }
        if (choose == 2)
            break;
    } while (choose == 1 || choose == 2);
}

void printSchedule(char *stdID)
{
    char *day = malloc(sizeof(char *) * MAXLINE);
    char *schel = malloc(sizeof(char *) * MAXLINE);
    strcpy(buf, "Enter a day (all to view all): ");
    strcpy(day, sendToClient(buf));
    printf("Select %s\n", day);
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
    sprintf(buf, "%-10s| %-30s| %-15s| %-15s| %-8s| %-20s| %-10s\n", "Code", "Course", "Week Day", "AM/PM", "Period", "Week", "Room");

    i = 0;
    while (i < courseTotal)
    {
        k = 0;
        while (k < j)
        {
            if (!strcmp(day, "all"))
            {
                if (!strcmp(courseSchedule[i].classCode, classCode[k]))
                {
                    sprintf(schel, "%-10s|%-31s| %-15s| %-15s| %d-%-6d| %-20s| %-10s\n", courseSchedule[i].courseCode, courseSchedule[i].courseName, convertWeekDayToString(courseSchedule[i].weekDay), convertSessionToString(courseSchedule[i].session), courseSchedule[i].startTime, courseSchedule[i].endTime, courseSchedule[i].week, courseSchedule[i].room);
                    strcat(buf, schel);
                }
            }
            else
            {
                if (!strcmp(courseSchedule[i].classCode, classCode[k]) && !strcmp(convertWeekDayToString(courseSchedule[i].weekDay), day))
                {
                    sprintf(schel, "%-10s|%-31s| %-15s| %-15s| %d-%-6d| %-20s| %-10s\n", courseSchedule[i].courseCode, courseSchedule[i].courseName, convertWeekDayToString(courseSchedule[i].weekDay), convertSessionToString(courseSchedule[i].session), courseSchedule[i].startTime, courseSchedule[i].endTime, courseSchedule[i].week, courseSchedule[i].room);
                    strcat(buf, schel);
                }
            }
            k++;
        }
        i++;
    }
    sendToClient(buf);
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
