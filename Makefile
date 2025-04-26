CC=gcc
CFLAGS=-Wall -pedantic -g 
BINARY=icsh

all: icsh

icsh: icsh.c
	$(CC) -o $(BINARY) $(CFLAGS) $<

.PHONY: clean

clean:
	rm -f $(BINARY)
