CFLAGS = -c -Wall
CC = gcc

all : main

main : main.o db.o controller.o
	${CC} main.o db.o controller.o -o main

main.o: main.c
	${CC} ${CFLAGS} main.c

db.o: db.c
	${CC} ${CFLAGS} db.c

controller.o: controller.c
	${CC} ${CFLAGS} controller.c

clean:
	rm -f *.o *~