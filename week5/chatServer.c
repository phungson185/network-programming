#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

#define MAXLINE 4096   /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8      /*maximum number of client connections*/

int main(int argc, char **argv)
{
    fd_set readfds;
    struct timeval tv;

    int listenfd, n, maxfd;
    socklen_t clilen;
    char buf[MAXLINE];
    struct sockaddr_in cliaddr, servaddr;

    int connfd1, connfd2;

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

    printf("%s\n", "Server running...waiting for connections.");

    connfd1 = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

    printf("%s\n", "Client 1 connected.");

    connfd2 = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

    printf("%s\n", "Client 2 connected.");

    close(listenfd);

    printf("%s\n", "Start talking...");

    tv.tv_sec = 300;

    maxfd = connfd2 > connfd1 ? connfd2 + 1 : connfd1 + 1;

    while (1)
    {
        // clear the set ahead of time
        FD_ZERO(&readfds);

        // add file descriptors to set
        FD_SET(connfd1, &readfds);
        FD_SET(connfd2, &readfds);

        int rv = select(maxfd, &readfds, NULL, NULL, &tv);

        if (rv == -1)
        {
            perror("select");
            exit(1);
        }
        else if (rv == 0)
        {
            printf("%s\n", "Timeout");
            break;
        }
        else
        {
            if (FD_ISSET(connfd1, &readfds))
            {
                memset(&buf, 0, MAXLINE);
                n = recv(connfd1, buf, MAXLINE, 0);
                send(connfd2, buf, n, 0);
                if (buf[0] == '\n')
                {
                    close(connfd1);
                    close(connfd2);
                    printf("%s\n", "...zzz...");
                    exit(0);
                }
                printf("%s\n", "Message from client 1: ");
                puts(buf);
            }
            if (FD_ISSET(connfd2, &readfds))
            {
                memset(buf, 0, MAXLINE);
                n = recv(connfd2, buf, MAXLINE, 0);
                send(connfd1, buf, n, 0);
                if (buf[0] == '\n')
                {
                    close(connfd1);
                    close(connfd2);
                    printf("%s\n", "...zzz...");
                    exit(0);
                }
                printf("%s\n", "Message from client 2: ");
                puts(buf);
            }
        }
    }       
}