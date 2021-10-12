#include "db.h"
#include "controller.h"

void init()
{
    getCourseSchedule("courseSchedule.txt");
    getStudentRegistration("studentRegistration.txt");
    getUserAccount("userAccount.txt");
}

int main(int argc, char *argv[])
{
    init();
    menu();
}