#include "bitsetget.h"
#include "LedNumber.h"
#include <iostream>
using namespace std;

int readSw(char* address, int swIdx);
void writeLED(char* address, int LEDIdx, int state);

/*
* Main Function
*/
int main() { 
// Initialize 
int fd; 
char *pBase = Initialize(&fd); 
    
// Sample test program
int value = 0; 
cout << "Enter an int value between 0 to 1023: " << endl; 
cin >> value; 
cout << "value to be written to LEDs = " << value << endl; 
WriteAllLeds(pBase, value);
int readLEDs = RegisterRead(pBase, LEDR_BASE);
cout << "value of LEDS read = " << readLEDs << endl;

// Done 
Finalize(pBase, fd); 
}

int readSw(char* address, int swIdx) {
    int registerVal = RegisterRead(address, SW_BASE);
    return readBitVal(registerVal, swIdx);
}
void writeLED(char* address, int LEDIdx, bool state) {
    RegisterWrite(address, LEDR_BASE, setBitVal(RegisterRead(address, LEDR_BASE), LEDIdx, state));
}