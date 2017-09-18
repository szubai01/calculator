all: q1.out

q1.out:	q1.o
	gcc -Wall -std=c99 q1.o -o q1.out

q1.o:	q1.c
	gcc -Wall -std=c99 -c q1.c

clean:
	rm *.o
