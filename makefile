CC=gcc
CFLAGS= -W -Wall -O
EXEC=main

main: main.c
	$(CC) -lm -o main main.c

clean:
	rm -rf $(EXEC)

all: main