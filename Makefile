CC=gcc
CFLAGS=-Wall -pedantic -g 
BINARY=icsh

all: icsh

icsh: icsh.o utility.o
	$(CC) -o $(BINARY) $(CFLAGS) icsh.o utility.o

icsh.o: icsh.c utility.h
	$(CC) $(CFLAGS) -c icsh.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c

.PHONY: clean

clean:
	rm -f $(BINARY) *.o
