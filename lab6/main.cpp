#include "bitsetget.h"
#include "LedNumber.h"
#include <iostream>
using namespace std;

int readSw(char* address, int swIdx);
void writeLED(char* address, int LEDIdx, int state);

int main() {

    return 1;
}

int readSw(char* address, int swIdx) {
    int registerVal = RegisterRead(address, SW_BASE);
    return readBitVal(registerVal, swIdx);
}
void writeLED(char* address, int LEDIdx, bool state) {
    RegisterWrite(address, LEDR_BASE, setBitVal(RegisterRead(address, LEDR_BASE), LEDIdx, state));
}