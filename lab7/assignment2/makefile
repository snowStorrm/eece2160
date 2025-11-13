main: DE1SoC.o DE1_HEX.o main.o
	g++ DE1SoC.o DE1_HEX.o main.o -o main.exe

DE1SoC.o: DE1SOC.cpp DE1SOC.h
	g++ -g -Wall -c DE1SOC.cpp

DE1_HEX.o: DE1_HEX.cpp DE1_HEX.h
	g++ -g -Wall -c DE1_HEX.cpp

main.o:
	g++ -g -Wall -c main.cpp

clean:
	rm main.exe main.o DE1SoC.o DE1_HEX.o