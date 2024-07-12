CC=gcc
CFLAGS=-I.
DEPS =
OBJ = server.o listener.o

server: server.o
	$(CC) -o build/server server.o $(CFLAGS)

listener: listener.o
	$(CC) -o build/listener listener.o $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: server listener
	rm *.o

clean:
	rm -r build/*

