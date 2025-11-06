#include "bitsetget.h"
#include "LedNumber.h"
#include <iostream>
using namespace std;

int readSw(char* address, int swIdx);
void writeLED(char* address, int LEDIdx, int state);

int main() { 
    int fd;
    char* pBase = Initialize(&fd);

    int val;
    cout << "Please enter the switch to read (0 - 9): ";
    cin >> val;
    cout << "Switch " << val << " is " << (readSw(pBase, val) ? " ON." : " OFF.") << endl;
    
    bool state;
    cout << "Please enter the LED to set (0 - 9): ";
    cin >> val;
    cout << "Please enter the state of this LED (0: off, 1: on): ";
    cin >> state;
    writeLED(pBase, val, state);
    cout << "Set LED " << val << " to " << (state ? " ON." : " OFF.") << endl;
}

int readSw(char* address, int swIdx) {
    int registerVal = RegisterRead(address, SW_BASE);
    return readBitVal(registerVal, swIdx);
}
void writeLED(char* address, int LEDIdx, bool state) {
    RegisterWrite(address, LEDR_BASE, setBitVal(RegisterRead(address, LEDR_BASE), LEDIdx, state));
}