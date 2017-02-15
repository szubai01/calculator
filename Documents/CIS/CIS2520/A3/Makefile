all: q1.out q2.out

q1.out:	q1.o
	gcc -Wall -std=c99 q1.o -o q1.out
	
q1.o:	q1.c
	gcc -Wall -std=c99 -c q1.c
	
q2.out:	q2.o
	gcc -Wall -std=c99 q2.o -o q2.out
	
q2.o:	q2.c
	gcc -Wall -std=c99 -c q2.c

clean:
	rm *.o
