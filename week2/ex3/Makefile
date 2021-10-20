CFLAGS = -Wall -o
CC = gcc

all : main

main :  
	${CC} ${CFLAGS} echoClient echoClient.c
	${CC} ${CFLAGS} echoServer echoServer.c db.c controller.c
	
clean:
	rm -f *.o *~