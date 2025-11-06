#include "bitsetget.h"

bool readBitVal(int val, int index) { return (val & (1 << index)) != 0; }
int setBitVal(int val, int index, bool set) { return (val - (val & (1 << index)) + (set << index)); }