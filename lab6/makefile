main: includes.o main.o
	g++ includes.o main.o -o main.exe

includes.o: LedNumber.cpp LedNumber.h
	g++ -g -Wall -c LedNumber.cpp

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm main.exe includes.o main.o