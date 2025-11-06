#include "bitsetget.h"
#include "PushButton.h"
#include <iostream>
using namespace std;

// Function declarations (see implementations below)
int getButtonPressed(int val);

int main() { 
    // Initialize memory mapping
    int fd;
    char* pBase = Initialize(&fd);

    // read the initial switch values and write them to the LEDs
    int val = RegisterRead(pBase, KEY_BASE);
    WriteAllLeds(pBase, val);
    // store the switch values as a bool array for state change checking
    bool prevState[4] = {readBitVal(val, 0), readBitVal(val, 1), readBitVal(val, 2), readBitVal(val, 3)};
    bool currState[4] = {prevState[0], prevState[1], prevState[2], prevState[3]};
    // loop infinitely until the user stops the program
    while (true) {
        
    }
    
}

int getButtonPressed(bool prevState[4], bool currState[4]) {
    // test if previous button state is different than current button state
    // default is -1 (i.e. do nothing)
    // if highestPressed is still its default value, set it to the index
    // if it's not, set it to 4 (i.e. multiple buttons have been pressed)
    int highestPressed = -1;
    if (prevState[0] != currState[0]) highestPressed = (highestPressed != -1 || highestPressed == 4) ? 4 : 0;
    if (prevState[1] != currState[1]) highestPressed = (highestPressed != -1 || highestPressed == 4) ? 4 : 1;
    if (prevState[2] != currState[2]) highestPressed = (highestPressed != -1 || highestPressed == 4) ? 4 : 2;
    if (prevState[3] != currState[3]) highestPressed = (highestPressed != -1 || highestPressed == 4) ? 4 : 3;
    // return the highestPressed
    return highestPressed;
}