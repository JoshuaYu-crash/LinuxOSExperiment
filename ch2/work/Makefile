all: server client

server: server.c
	gcc -o server server.c semshm.h

client: client.c
	gcc -o client client.c semshm.h