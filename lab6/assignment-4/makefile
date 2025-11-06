main: de1soc.o main.o
	g++ de1soc.o main.o -o main.exe

de1soc.o: de1soc.cpp de1soc.h
	g++ -g -Wall -c de1soc.cpp

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm main.exe de1soc.o main.o