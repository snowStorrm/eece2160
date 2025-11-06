#include "bitsetget.h"
#include "LedNumber.h"
#include <iostream>
using namespace std;

// Function declarations (see implementations below)
bool readSw(char* address, int swIdx);
void writeLED(char* address, int LEDIdx, bool state);

int main() { 
    // Initialize memory mapping
    int fd;
    char* pBase = Initialize(&fd);

    // Read a switch value
    int val;
    cout << "Please enter the switch to read (0 - 9): ";
    cin >> val;
    // Ternary operator statement to convert true or false into on/off
    cout << "Switch " << val << " is " << (readSw(pBase, val) ? " ON." : " OFF.") << endl;
    
    // Set an LED value
    bool state;
    cout << "Please enter the LED to set (0 - 9): ";
    cin >> val;
    cout << "Please enter the state of this LED (0: off, 1: on): ";
    cin >> state;
    // Write the value
    writeLED(pBase, val, state);
    // Ternary operator statement to convert true/false to on/off
    cout << "Set LED " << val << " to " << (state ? " ON." : " OFF.") << endl;
    Finalize(pBase, fd);
}


/** Reads the state of a single specified switch
 *  @param address      Base address for GPIO
 *  @param swIdx        Which switch to read (0 - 9)
 *  @return             Boolean value representing switch state
 */
bool readSw(char* address, int swIdx) {
    // Read the entire 4-byte register value
    int registerVal = RegisterRead(address, SW_BASE);
    // Read one specific bit of that value
    return readBitVal(registerVal, swIdx);
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