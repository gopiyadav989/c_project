#Makefile


all: example

example: example.o libarcfour.a
	gcc example.o -L. -larcfour -o example

example.o: example.c
	gcc -c example.c

libarcfour.a: arcfour.o
	ar rcs libarcfour.a arcfour.o

arcfour.o: arcfour.c
	gcc -c arcfour.c

clean:
	rm -f *.o example libarcfour.a





# before running the command it create all the dependencies file
