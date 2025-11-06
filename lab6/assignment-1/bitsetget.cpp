#include "bitsetget.h"

/** Reads one specific bit of an integer.
 *  @param val      The value to read
 *  @param index    The index of the bit to read
 *  @return         Boolean representing the state of the bit
 */
bool readBitVal(int val, int index) { return (val & (1 << index)) != 0; }
/** Writes one specific bit of an integer.
 *  @param val      The value to write to
 *  @param index    The index of the bit to write
 *  @param set      Boolean representing the new state of the bit
 *  @return         The updated value
 */
int setBitVal(int val, int index, bool set) { return (val - (val & (1 << index)) + (set << index)); }