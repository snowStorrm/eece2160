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

}
int readSw(char* address, int swIdx) {
    // Read the entire 4-byte register value
    int registerVal = RegisterRead(address, SW_BASE);
    // Read one specific bit of that value
    return readBitVal(registerVal, swIdx);
}

int readAllSw(char* address) {
    // Read the entire 4-byte register value
    return RegisterRead(address, SW_BASE);
}

void writeLED(char* address, int LEDIdx, bool state) {
    // Read the entire 4-byte register value, set a specific bit in that value, then write to the same register
    RegisterWrite(address, LEDR_BASE, setBitVal(RegisterRead(address, LEDR_BASE), LEDIdx, state));
}