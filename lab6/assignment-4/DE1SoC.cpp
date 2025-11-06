#include "DE1SOC.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

/** Initialize general-purpose I/O 
 *  - Opens access to physical memory /dev/mem 
 *  - Maps memory into virtual address space 
 */ 
void DE1SOC::DE1SOC() {
	// Open /dev/mem to give access to physical addresses
	this->*fd = open( "/dev/mem", (O_RDWR | O_SYNC));
	if (this->*fd == -1) {// check for errors in openning /dev/mem
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
    }
    // Get a mapping from physical addresses to virtual addresses
    char* virtual_base = (char*)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, this->*fd, LW_BRIDGE_BASE);
    if (virtual_base == MAP_FAILED)	{	// check for errors
        cout << "ERROR: mmap() failed..." << endl;
        close (this->*fd); // close memory before exiting
        exit(1); // Returns 1 to the operating system;
    }
    this->pBase=virtual_base;
}

/** Close general-purpose I/O. 
 */ 
void DE1SOC::~DE1SOC() {
	if (munmap (this->pBase, LW_BRIDGE_SPAN) != 0) {
        cout << "ERROR: munmap() failed..." << endl;
        exit(1);
    }
    close (this->fd); // close memory
}

/** Write a 4-byte value at the specified general-purpose I/O location. 
 *  @param reg_offset	Offset where device is mapped. 
 *  @param value	    Value to be written. 
 */ 
void DE1SOC::registerWrite(unsigned int reg_offset, int value) { *(volatile unsigned int*)(this->pBase + reg_offset) = value; }
/** Read a 4-byte value from the specified general-purpose I/O location. 
 *  @param offset	    Offset where device is mapped. 
 *  @return		        Value read. 
 */ 
int DE1SOC::registerRead(unsigned int reg_offset) { return *(volatile unsigned int*)(this->pBase + reg_offset); } 

/** Writes the state of a single specified LED
 *  @param board        C++ Instance of the DE1-SoC
 *  @param LEDIdx       Which LED to set (0 - 9)
 *  @param state        Boolean value representing LED state
 */
void writeLED(DE1SOC* board, int LEDIdx, bool state) { board->registerWrite(LEDR_BASE, setBitVal(board->registerRead(LEDR_BASE), LEDIdx, state)); }
/** Show the input integer value on LEDs
 *  - Calls RegisterWrite to set all LEDs 
 *  @param board        C++ Instance of the DE1-SoC
 *  @param value	    Value to show on LEDs
 */
void writeAllLEDs(DE1SOC* board, int value) { board->registerWrite(LEDR_BASE, value); }

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

/** Reads the state of a single specified switch
 *  @param board        C++ Instance of the DE1-SoC
 *  @param swIdx        Which switch to read (0 - 9)
 *  @return             Boolean value representing switch state
 */
bool readSwitch(DE1SOC* board, int swIdx) {
    // Read the entire 4-byte register value
    int registerVal = board->registerRead(SW_BASE);
    // Read one specific bit of that value
    return readBitVal(registerVal, swIdx);
}
/** Reads all switches and returns their value as a single int.
 *  @param board        C++ Instance of the DE1-SoC
 *  @return             Int representing switch values
 */
int readAllSwitches(DE1SOC* board) { return board->registerRead(SW_BASE); }

/** Gets the current push button pressed based on state data
 *  @param board        C++ Instance of the DE1-SoC
 *  @return             Int representing the current button pressed. 
 *                      - Returns -1 if no buttons pressed, 4 if multiple buttons pressed.
 */
int getButtonPressed(DE1SOC* board) {
    // get the state of all push buttons
    int currButtonVal = board->registerRead(KEY_BASE);
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