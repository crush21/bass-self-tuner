# Makefile that generates executable getAnalog file.

CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=-lfftw3 -lm

all: getAnalog motor

getAnalog: getAnalog.o
	$(CC) -o getAnalog getAnalog.o $(LDFLAGS)
	rm getAnalog.o

motor: motor.o
	$(CC) -o motor motor.o
	rm motor.o

getAnalog.o: analogCode/getAnalog.cpp
	$(CC) $(CFLAGS) -o getAnalog.o analogCode/getAnalog.cpp $(OTHERFLAGS)

motor.o: motorCode/motor.cpp
	$(CC) $(CFLAGS) -o motor.o motorCode/motor.cpp $(OTHERFLAGS)

clean:
	rm -f *o getAnalog motor
