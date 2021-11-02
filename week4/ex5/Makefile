CFLAGS = -Wall -o
CC = gcc

all : main

main :  
	${CC} ${CFLAGS} echoClient echoClient.c
	${CC} ${CFLAGS} conEchoServer conEchoServer.c db.c controller.c
	
clean:
	rm -f *.o *~