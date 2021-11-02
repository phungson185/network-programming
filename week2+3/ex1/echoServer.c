#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define MAXLINE 4096   /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8      /*maximum number of client connections */

int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    char buf[MAXLINE];
    struct sockaddr_in cliaddr, servaddr;

    //creation of the socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //preparation of the socket address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 1);

    printf("%s\n", "Server running...waiting for connections.");

    for (;;)
    {

        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        
        sprintf(buf, "%s:%d", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
        printf("%s\n", "Received request...");

        if (send(connfd, buf, strlen(buf), 0) < 0)
        {
            perror("Read error");
            exit(1);
        }
        if (recv(connfd, buf, MAXLINE, 0) == 0)
        {
            //error: server terminated prematurely
            perror("The server terminated prematurely");
            exit(4);
        }
        close(connfd); 
    }
    //close listening socket
    close(listenfd);
}