main: PushButton.o bitsetget.o main.o
	g++ PushButton.o bitsetget.o main.o -o main.exe

PushButton.o: PushButton.cpp PushButton.h
	g++ -g -Wall -c PushButton.cpp

bitsetget.o: bitsetget.cpp bitsetget.h
	g++ -g -Wall -c bitsetget.cpp

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm main.exe PushButton.o bitsetget.o main.o