# Makefile that generates executable getAnalog file.

CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=-fftw3 -lm
SOURCES=getAnalog.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=getAnalog

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(OTHERFLAGS)

#CC=g++

#CFLAGS=-c -Wall -O2

#all: getAnalog

#getAnalog: getAnalog.o
#	$(CC) getAnalog.o -o getAnalog -lfftw3 -lm
#	rm -f getAnalog.o

#getAnalog.o: getAnalog.cpp
#	$(CC) $(CFLAGS) getAnalog.cpp

clean:
	rm -f *o $(EXECUTABLE)
