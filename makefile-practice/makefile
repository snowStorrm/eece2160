$(MAIN) = DE1SoCMain
$(DE1SoC) = DE1SoC

main: includes.o main.o
	g++ includes.o main.o -o main.exe

includes.o: $(DE1SoC).cpp $(DE1SoC).h
	g++ -g -Wall -c $(DE1SoC).cpp

main.o: $(MAIN).cpp
	g++ -g -Wall -c $(MAIN).cpp

clean:
	rm main.exe includes.o main.o