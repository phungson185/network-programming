#include "db.h"
#include "controller.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void init()
{
    getCourseSchedule("courseSchedule.txt");
    getStudentRegistration("studentRegistration.txt");
    getUserAccount("userAccount.txt");
}

int main(int argc, char **argv)
{
    int listenfd ;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    //creation of the socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //preparation of the socket address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, LISTENQ);

    init();

    printf("%s\n", "Server running...waiting for connections.");

    for (;;)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        printf("%s\n", "Received request...");
        menu();
        close(connfd);
    }
    //close listening socket
    close(listenfd);
}