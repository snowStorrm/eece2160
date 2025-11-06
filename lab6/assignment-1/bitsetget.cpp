#include "bitsetget.h"

// Read a bit of a given number. returns true if on and false if off.
bool readBitVal(int val, int index) { return (val & (1 << index)) != 0; }
// Set a bit of a given number.
int setBitVal(int val, int index, bool set) { return (val - (val & (1 << index)) + (set << index)); }