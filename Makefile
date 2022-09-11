CC=gcc
LIBS=-lpthread

out:main.o
	${CC} -g main.o -o out ${LIBS}

main.o:main.c
	${CC} -g -c main.c -o main.o

clean:
	rm *.o