main: LedNumber.o bitsetget.o main.o
	g++ LedNumber.o main.o -o main.exe

LedNumber.o: LedNumber.cpp LedNumber.h
	g++ -g -Wall -c LedNumber.cpp

bitsetget.o: bitsetget.cpp bitsetget.h
	g++ -g -Wall -c bitsetget.cpp

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm main.exe LedNumber.o bitsetget.o main.o