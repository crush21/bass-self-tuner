# Makefile that generates executable getAnalog file.

CC=g++
CFLAGS=-c -Wall -O2
LDFLAGS=-lfftw3 -lm

all: allAnalog allMotor lcd


allAnalog: s1Analog s2Analog s3Analog s4Analog

s1Analog: s1Analog.o
	$(CC) -o s1Analog s1Analog.o $(LDFLAGS)
	rm s1Analog.o

s1Analog.o: analog/s1Analog.cpp
	$(CC) $(CFLAGS) -o s1Analog.o analog/s1Analog.cpp

s2Analog: s2Analog.o
	$(CC) -o s2Analog s2Analog.o $(LDFLAGS)
	rm s2Analog.o

s2Analog.o: analog/s2Analog.cpp
	$(CC) $(CFLAGS) -o s2Analog.o analog/s2Analog.cpp

s3Analog: s3Analog.o
	$(CC) -o s3Analog s3Analog.o $(LDFLAGS)
	rm s3Analog.o

s3Analog.o: analog/s3Analog.cpp
	$(CC) $(CFLAGS) -o s3Analog.o analog/s3Analog.cpp

s4Analog: s4Analog.o
	$(CC) -o s4Analog s4Analog.o $(LDFLAGS)
	rm s4Analog.o

s4Analog.o: analog/s4Analog.cpp
	$(CC) $(CFLAGS) -o s4Analog.o analog/s4Analog.cpp


allMotor: runMotor1 runMotor2 runMotor3 runMotor4

runMotor1: runMotor1.o
	$(CC) -o runMotor1 runMotor1.o
	rm runMotor1.o

runMotor1.o: motor/runMotor1.cpp
	$(CC) $(CFLAGS) -o runMotor1.o motor/runMotor1.cpp

runMotor2: runMotor2.o
	$(CC) -o runMotor2 runMotor2.o
	rm runMotor2.o

runMotor2.o: motor/runMotor2.cpp
	$(CC) $(CFLAGS) -o runMotor2.o motor/runMotor2.cpp

runMotor3: runMotor3.o
	$(CC) -o runMotor3 runMotor3.o
	rm runMotor3.o

runMotor3.o: motor/runMotor3.cpp
	$(CC) $(CFLAGS) -o runMotor3.o motor/runMotor3.cpp

runMotor4: runMotor4.o
	$(CC) -o runMotor4 runMotor4.o
	rm runMotor4.o

runMotor4.o: motor/runMotor4.cpp
	$(CC) $(CFLAGS) -o runMotor4.o motor/runMotor4.cpp


lcd: lcd.o
	$(CC) -o lcd lcd.o
	rm lcd.o

lcd.o: display/lcd.cpp
	$(CC) $(CFLAGS) -o lcd.o display/lcd.cpp 


clean:
	rm -f *o s1Analog s2Analog s3Analog s4Analog runMotor1 runMotor2 runMotor3 runMotor4 lcd
