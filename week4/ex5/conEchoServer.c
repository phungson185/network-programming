#include "db.h"
#include "controller.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>

void sig_chld(int signo)
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);
    return;
}

void init()
{
    getCourseSchedule("courseSchedule.txt");
    getStudentRegistration("studentRegistration.txt");
    getUserAccount("userAccount.txt");
}

int main(int argc, char **argv)
{
    int listenfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    //Create a socket for the soclet
    //If sockfd<0 there was an error in the creation of the socket
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Problem in creating the socket");
        exit(2);
    }

    //preparation of the socket address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    //bind the socket
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    //listen to the socket by creating a connection queue, then wait for clients
    listen(listenfd, LISTENQ);

    init();

    printf("%s\n", "Server running...waiting for connections.");

    for (;;)
    {

        clilen = sizeof(cliaddr);
        //accept a connection
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

        printf("%s\n", "Received request...");

        if ((childpid = fork()) == 0)
        { //if it’s 0, it’s child process

            printf("%s\n", "Child created for dealing with client requests");

            //close listening socket
            close(listenfd);

            // while ((n = recv(connfd, buf, MAXLINE, 0)) > 0)
            // {
            //     printf("%s", "String received from and resent to the client:");
            //     puts(buf);
            //     send(connfd, buf, n, 0);
            // }

            menu();

            // if (n < 0)
            //     printf("%s\n", "Read error");

            exit(0);
        }
        signal(SIGCHLD, sig_chld);

        //close socket of the server
        close(connfd);
    }
}