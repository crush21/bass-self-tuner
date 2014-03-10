# Makefile that generates executable getAnalog file.

CC=g++

CFLAGS=-c -Wall -O2

all: getAnalog

getAnalog: getAnalog.o
	$(CC) getAnalog.o -o getAnalog -lfftw3 -lm
	rm -f getAnalog.o

getAnalog.o: getAnalog.cpp
	$(CC) $(CFLAGS) getAnalog.cpp

clean:
	rm -f *o getAnalog
