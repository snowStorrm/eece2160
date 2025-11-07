#include "bitsetget.h"
#include "PushButton.h"
#include <iostream>
using namespace std;

// Function declarations (see implementations below)
int readAllSw(char* address);
void writeLED(char* address, int LEDIdx, bool state);
int getButtonPressed(bool currState[4]);

int main() { 
    // Initialize memory mapping
    int fd;
    char* pBase = Initialize(&fd);

    // read the initial switch values and write them to the LEDs
    int initialSw = readAllSw(pBase);
    WriteAllLeds(pBase, initialSw);

    // remember current and previous state
    int prevButton = -1, currButton = -1;

    // loop infinitely until the user Ctrl+C quits
    while (true) {
        // get LED register value and push button register value
        int currLEDVal = RegisterRead(pBase, LEDR_BASE);
        int currButtonVal = RegisterRead(pBase, KEY_BASE);
        // convert push button register value into array to be passed into getButtonPressed()
        bool currState[4] = {readBitVal(currButtonVal, 0), readBitVal(currButtonVal, 1), readBitVal(currButtonVal, 2), readBitVal(currButtonVal, 3)};
        currButton = getButtonPressed(currState);
        // if the input has changed, do an operation based on the state change
        if (currButton != prevButton) switch (currButton) {
            // add 1 to LED value
            case 0: WriteAllLeds(pBase, currLEDVal+1); break;
            // sub 1 from LED value
            case 1: WriteAllLeds(pBase, currLEDVal-1); break;
            // bit shift right (divide by 2)
            case 2: WriteAllLeds(pBase, currLEDVal>>1); break;
            // bit shift left (mult by 2)
            case 3: WriteAllLeds(pBase, currLEDVal<<1); break;
            // set to current physical switch configuration
            case 4: WriteAllLeds(pBase, readAllSw(pBase)); break;
        }
        // set the previous input to the current one
        prevButton = currButton;
        // simple delay loop to slow the program down a little
        for (int i = 0; i < 2500; i++) {};
    }
}

/** Reads all switches and returns their value as a single int.
 *  @param address      Base address for GPIO
 *  @return             Int representing switch values
 */
int readAllSw(char* address) {
    // Read the entire 4-byte register value
    return RegisterRead(address, SW_BASE);
}

/** Writes the state of a single specified LED
 *  @param address      Base address for GPIO
 *  @param LEDIdx       Which LED to set (0 - 9)
 *  @param state        Boolean value representing LED state
 */
void writeLED(char* address, int LEDIdx, bool state) {
    // Read the entire 4-byte register value, set a specific bit in that value, then write to the same register
    RegisterWrite(address, LEDR_BASE, setBitVal(RegisterRead(address, LEDR_BASE), LEDIdx, state));
}

/** Gets the current push button pressed based on state data
 *  @param currState        The current state data of the buttons
 *  @return                 Int representing the current button pressed. Returns -1 if no buttons pressed, 4 if multiple buttons pressed.
 */
int getButtonPressed(bool currState[4]) {
    // default is -1 (i.e. do nothing)
    // if highestPressed is still its default value, set it to the index
    // if it's not, set it to 4 (i.e. multiple buttons have been pressed)
    int highestPressed = -1;
    if (currState[0]) highestPressed = (highestPressed != -1) ? 4 : 0;
    if (currState[1]) highestPressed = (highestPressed != -1) ? 4 : 1;
    if (currState[2]) highestPressed = (highestPressed != -1) ? 4 : 2;
    if (currState[3]) highestPressed = (highestPressed != -1) ? 4 : 3;
    // return the value
    return highestPressed;
}