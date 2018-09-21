all:
	gcc -c main.c
	gcc -c bitmap.c
	gcc -c list.c
	gcc -c hash.c
	gcc -o testlib -Wall main.o bitmap.o list.o hash.o

clean:
	rm testlib *.o
