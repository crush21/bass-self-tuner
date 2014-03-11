# Makefile that generates executable getAnalog file.

CC=g++
CFLAGS=-c -Wall -O2
#LDFLAGS=-fftw3 -lm
SOURCES=motor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=motor

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(SOURCES) $(OTHERFLAGS)

#CC=g++

#CFLAGS=-c -Wall -O2

#all: motor

#motor: motor.o
#	$(CC) motor.o -o motor -lfftw3 -lm
#	rm -f motor.o

#motor.o: motor.cpp
#	$(CC) $(CFLAGS) motor.cpp

clean:
	rm -f *o $(EXECUTABLE)
