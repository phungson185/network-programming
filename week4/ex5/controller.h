#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

void login();
void menu();
void schedule(char* stdID);
void printSchedule(char* stdID);
char *convertWeekDayToString(int weekDay);
char *convertSessionToString(int session);

#define MAXLINE 4096   /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8      /*maximum number of client connections */

int connfd;
char buf[MAXLINE];

#endif