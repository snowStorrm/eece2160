// Include libraries
#include "bitsetget.h"
#include "LedNumber.h"
#include <iostream>
using namespace std;

// Function declarations (see implementations below)
int readSw(char* address, int swIdx);
int readAllSw(char* address);
void writeLED(char* address, int LEDIdx, bool state);

int main() { 
    // Initialize memory mapping
    int fd;
    char* pBase = Initialize(&fd);

    // Read all switch values
    int val = readAllSw(pBase);
    cout << "The switch values are " << val << endl;
    // Write the read value to the LEDs
    cout << "Writing " << val << " to the LEDs."; 
    WriteAllLeds(pBase, val);
    Finalize(pBase, fd);
}

/** Reads the state of a single specified switch
 *  @param address      Base address for GPIO
 *  @param swIdx        Which switch to read (0 - 9)
 *  @return             Boolean value representing switch state
 */
int readSw(char* address, int swIdx) {
    // Read the entire 4-byte register value
    int registerVal = RegisterRead(address, SW_BASE);
    // Read one specific bit of that value
    return readBitVal(registerVal, swIdx);
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