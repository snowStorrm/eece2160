#include "DE1_HEX.h"
#include <iostream>
#include <string>
using namespace std;

/** Clears the HEX displays before destroying the DE1_HEX object.
 */
DE1_HEX::~DE1_HEX() { 
    this->clearAll(); 
}

/** Sets both HEX registers to zero, clearing them.
 */
void DE1_HEX::clearAll() {
    this->reg0 = 0;
    this->reg1 = 0;
    this->registerWrite(HEX3_HEX0_BASE, this->reg0);
    this->registerWrite(HEX5_HEX4_BASE, this->reg1);
}

/** Clears a specific HEX display.
 *  @param index        The index of the HEX display to clear (0 - 5).
 */
void DE1_HEX::clear(int index) {
    // 0-3: we want to write to reg0 
    if (index>=0 && index<=3) {
        // largely similar to DE1SOC::setBitVal()
        // create a mask to cover the target area
        // subtract that area's value from the entire register, setting all nonzero bits to zero
        this->reg0=this->reg0 - (this->reg0 & (255 << (index * 8)));
        this->registerWrite(HEX3_HEX0_BASE, this->reg0);
    // 4-5: we want to write to reg1
    } else if (index>=4 && index<=5) {
        // see above comments
        this->reg1=this->reg1 - (this->reg1 & (255 << ((index-4) * 8)));
        this->registerWrite(HEX5_HEX4_BASE, this->reg1);
    // error if not in range
    } else { cout << "Error: invalid HEX index. Valid ranges are 0-5.\n"; };
}

/** Sets the entire DE1 HEX display to a given string.
 *  - If string is shorter than six characters, remaining displays will be empty.
 *  - If string is longer than six characters, only the first six characters will be shown.
 *  @param value        The string to display on the HEX displays.
 */
void DE1_HEX::setAll(string value) {
    // get length of string
    int len = value.size();
    // for each HEX display, test if we have reached end of string
    for (int i = 0; i < 6; i++) {
        // if within the string, set the corresponding display to the value
        if (i <= len) {
            this->set(i, value[i]);
        // otherwise, set it to an empty value
        } else this->set(i, ' ');
    }
}

/** Sets a specific HEX display to a given value.
 *  @param index        The index of the HEX display to set (0 - 5).
 *  @param value        The character to display (012345689abcdef-). Case sensitive. 
 */
void DE1_HEX::set(int index, char value) {
    // we can use a decoder string to effectively eliminate the 16-long if-else if-else or switch case
    string decode = "0123456789abcdef-";
    // each value represents the decimal version of the HEX segment on/off. see lab report for a table.
    int values[17] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 119, 124, 57, 94, 121, 113, 64};
    int valueToSet;
    size_t i = decode.find(value);
    // if we didn't find the character in the decode string, the char should be set to empty
    if (i == string::npos) valueToSet = 0;
    // otherwise, the index returned corresponds 1:1 to values[i]
    else valueToSet = values[i];

    // write the value
    // 0-3: we want to write to reg0 
    if (index>=0 && index<=3) {
        // largely similar to DE1SOC::setBitVal()
        // create a mask to cover the target area
        // subtract that area's value from the entire register, setting all nonzero bits to zero
        // finally, we add the new value bitshifted to the correct register position
        this->reg0=this->reg0 - (this->reg0 & (255 << (index * 8))) + (valueToSet << (index * 8));
        this->registerWrite(HEX3_HEX0_BASE, this->reg0);
    // 4-5: we want to write to reg1
    } else if (index>=4 && index<=5) {
        // see above comments
        this->reg1=this->reg1 - (this->reg1 & (255 << ((index-4) * 8))) + (valueToSet << ((index-4) * 8));
        this->registerWrite(HEX5_HEX4_BASE, this->reg1);
    // error if not in range
    } else { cout << "Error: invalid HEX index. Valid ranges are 0-5.\n"; };
}
