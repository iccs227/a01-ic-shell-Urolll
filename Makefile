CC=gcc
CFLAGS=-Wall -pedantic -g 
BINARY=icsh

all: icsh

icsh: icsh.o utility.o signal.o jobs.o
	$(CC) -o $(BINARY) $(CFLAGS) icsh.o utility.o signal.o jobs.o

icsh.o: icsh.c utility.h
	$(CC) $(CFLAGS) -c icsh.c

utility.o: utility.c utility.h
	$(CC) $(CFLAGS) -c utility.c

signal.o: signal.c signal.h
	$(CC) $(CFLAGS) -c signal.c

jobs.o: jobs.c jobs.h
	$(CC) $(CFLAGS) -c jobs.c

.PHONY: clean

clean:
	rm -f $(BINARY) *.o
