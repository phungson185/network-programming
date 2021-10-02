#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

void login();
void menu();
void schedule(char* stdID);
void printSchedule(char* stdID);
char *convertWeekDayToString(int weekDay);
char *convertSessionToString(int session);

#endif