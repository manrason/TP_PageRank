CC=gcc
CFLAGS= -W -Wall -o
EXEC=PageRank

PageRank: PageRank.c
	$(CC) ${CFLAGS} PageRank PageRank.c -lm

clean:
	rm -rf $(EXEC)

all: PageRank