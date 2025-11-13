#include "DE1SoC.h"
#include "DE1_LED.h"

/** Writes the state of a single specified LED
 *  @param LEDIdx       Which LED to set (0 - 9)
 *  @param state        Boolean value representing LED state
 */
void DE1_LED::writeLED(int LEDIdx, bool state) { 
    this->reg = setBitVal(this->registerRead(LEDR_BASE), LEDIdx, state);
    this->registerWrite(LEDR_BASE, this->reg); 
}
/** Show the input integer value on LEDs
 *  - Calls RegisterWrite to set all LEDs 
 *  @param value	    Value to show on LEDs
 */
void DE1_LED::writeAllLEDs(int value) { 
    this->reg = value;
    this->registerWrite(LEDR_BASE, this->reg); 
}

/** Reads the state of a single specified switch
 *  @param swIdx        Which switch to read (0 - 9)
 *  @return             Boolean value representing switch state
 */
bool DE1_LED::readSwitch(int swIdx) {
    // Read the entire 4-byte register value
    int registerVal = this->registerRead(SW_BASE);
    // Read one specific bit of that value
    return readBitVal(registerVal, swIdx);
}
/** Reads all switches and returns their value as a single int.
 *  @return             Int representing switch values
 */
int DE1_LED::readAllSwitches() { return this->registerRead(SW_BASE); }

/** Gets the current push button pressed based on state data
 *  @return             Int representing the current button pressed. 
 *                      - Returns -1 if no buttons pressed, 4 if multiple buttons pressed.
 */
int DE1_LED::getButtonPressed() {
    // get the state of all push buttons
    int currButtonVal = this->registerRead(KEY_BASE);
    // split into an array
    bool currState[4] = {readBitVal(currButtonVal, 0), readBitVal(currButtonVal, 1), readBitVal(currButtonVal, 2), readBitVal(currButtonVal, 3)};
    // default is -1 (i.e. do nothing)
    // if highestPressed is still its default value, set it to the index
    // if it's not, set it to 4 (i.e. multiple buttons have been pressed)
    int highestPressed = -1;
    if (currState[0]) highestPressed = (highestPressed != -1) ? 4 : 0;
    if (currState[1]) highestPressed = (highestPressed != -1) ? 4 : 1;
    if (currState[2]) highestPressed = (highestPressed != -1) ? 4 : 2;
    if (currState[3]) highestPressed = (highestPressed != -1) ? 4 : 3;
    // return the value
    return highestPressed;
}