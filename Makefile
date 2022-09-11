CC=gcc
LIBS=-lpthread

out:main.o
	${CC} -g main.o -o out ${LIBS}

main.o:main.c
<<<<<<< HEAD
	${CC} -g -c main.c -o main.o

clean:
	rm *.o
=======
	${CC} -g -c main.c -o main.o
>>>>>>> 7c32a27865879b9205108dc8fc063b6bdae468d4
