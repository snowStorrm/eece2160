#include "DE1SoC.h"
#include "DE1_LED.h"
#include "DE1_HEX.h"
#include <iostream>
#include <stdio.h>
using namespace std;

int main() { 
    // Initialize HEX and LED controllers
    DE1_LED* LED = new DE1_LED();
    DE1_HEX* HEX = new DE1_HEX();

    // read the initial switch values and write them to the LEDs
    int initialSw = LED->readAllSwitches();
    LED->writeAllLEDs(initialSw);

    // remember current and previous state
    int prevButton = -1, currButton = -1;

    // loop infinitely until the user Ctrl+C quits
    while (true) {
        // get LED register value
        // determine button(s) pressed
        currButton = LED->getButtonPressed();
        // if the input has changed, do an operation based on the state change
        if (currButton != prevButton) switch (currButton) {
            // add 1 to LED value
            case 0: LED->writeAllLEDs(LED->reg+1); break;
            // sub 1 from LED value
            case 1: LED->writeAllLEDs(LED->reg-1); break;
            // bit shift right (divide by 2)
            case 2: LED->writeAllLEDs(LED->reg>>1); break;
            // bit shift left (mult by 2)
            case 3: LED->writeAllLEDs(LED->reg<<1); break;
            // set to current physical switch configuration
            case 4: LED->writeAllLEDs(LED->readAllSwitches()); break;
        }
        // set the previous input to the current one
        prevButton = currButton;
        // display value on hex displays
        // convert to string manually since to_string() isn't available
        char valueAsString[50];
        sprintf(valueAsString, "%d", LED->reg);
        HEX->setAll((const string&)(valueAsString));
        // simple delay loop to slow the program down a little
        for (int i = 0; i < 2500; i++) {};
    }
    // destroy HEX and LED controllers
    HEX->~DE1_HEX();
    LED->~DE1_LED();
}