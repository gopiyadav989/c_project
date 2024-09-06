##Makefile chat_server
all: client server

client: client.o ../arc4/libarcfour.a
	gcc client.o -L../arc4 -larcfour -o Client

server: server.o ../arc4/libarcfour.a
	gcc server.o -L../arc4 -larcfour -o Server

client.o: client.c
	gcc -c client.c -I../arc4

server.o: server.c
	gcc -c server.c -I../arc4

clean:
	rm -f *.o Client Server
