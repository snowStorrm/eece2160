#include "DE1SoC.h"
#include <iostream>
#include <chrono>
using namespace std;

int main() { 
    // Initialize memory mapping
    DE1SOC* board = new DE1SOC();

    // read the initial switch values and write them to the LEDs
    int initialSw = readAllSwitches(board);
    writeAllLEDs(board, initialSw);

    // remember current and previous state
    int prevButton = -1, currButton = -1;

    // loop infinitely until the user Ctrl+C quits
    while (true) {
        // get LED register value
        int currLEDVal = board->registerRead(LEDR_BASE);
        // determine button(s) pressed
        currButton = getButtonPressed(board);
        // if the input has changed, do an operation based on the state change
        if (currButton != prevButton) switch (currButton) {
            case 0: writeAllLEDs(board, currLEDVal+1); break;
            case 1: writeAllLEDs(board, currLEDVal-1); break;
            case 2: writeAllLEDs(board, currLEDVal>>1); break;
            case 3: writeAllLEDs(board, currLEDVal<<1); break;
            case 4: writeAllLEDs(board, readAllSwitches(board)); break;
        }
        // set the previous input to the current one
        prevButton = currButton;
        // simple delay loop to slow the program down a little
        for (int i = 0; i < 2500; i++) {};
    }
    board->~DE1SOC();
}