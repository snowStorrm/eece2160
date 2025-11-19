main: DE1SoC.o main.o
	g++ DE1SoC.o main.o -o main.exe

DE1SoC.o: DE1SoC.h DE1SoC.cpp
	g++ -g -Wall -c DE1SoC.cpp

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm main.exe main.o DE1SoC.o