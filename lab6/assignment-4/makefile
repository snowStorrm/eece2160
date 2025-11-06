main: DE1SoC.o main.o
	g++ de1soc.o main.o -o main.exe

DE1SoC.o: DE1SoC.cpp DE1SoC.h
	g++ -g -Wall -c DE1SoC.cpp

main.o: main.cpp
	g++ -g -Wall -c main.cpp

clean:
	rm main.exe de1soc.o main.o