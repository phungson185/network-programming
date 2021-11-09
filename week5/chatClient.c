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

int main(int argc, char **argv)
{
    fd_set readfds;
    struct timeval tv;

    int sockfd, maxfd;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];

    //basic check of the arguments
    //additional checks can be inserted
    if (argc != 2)
    {
        perror("Usage: TCPClient <IP address of the server");
        exit(1);
    }

    //Create a socket for the client
    //If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Problem in creating the socket");
        exit(2);
    }

    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(SERV_PORT); //convert to big-endian order

    //Connection of the client to the socket
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Problem in connecting to the server");
        exit(3);
    }

    tv.tv_sec = 300;

    maxfd = sockfd + 1;

    while (1)
    {
        // clear the set ahead of time
        FD_ZERO(&readfds);

        // add file descriptors to set
        FD_SET(0, &readfds);
        FD_SET(sockfd, &readfds);

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
            if (FD_ISSET(sockfd, &readfds))
            {
                memset(&recvline, 0, MAXLINE);
                if (recv(sockfd, recvline, MAXLINE, 0) == 0)
                {
                    perror("Server terminated prematurely");
                    exit(1);
                }
                if (recvline[0] == '\n')
                {
                    close(sockfd);
                    printf("%s\n", "Your friend ended the chat");
                    exit(0);
                }
                printf("%s", "Message from your friend: ");
                fputs(recvline, stdout);
            }
            if (FD_ISSET(0, &readfds))
            {
                memset(&sendline, 0, MAXLINE);
                fgets(sendline, MAXLINE, stdin);
                send(sockfd, sendline, strlen(sendline), 0);
                if (sendline[0] == '\n')
                {
                    close(sockfd);
                    printf("%s\n", "You ended the chat");
                    exit(0);
                }
            }
        }
    }
    exit(0);
}