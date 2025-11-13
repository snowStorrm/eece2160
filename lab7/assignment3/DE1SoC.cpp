#include "DE1SoC.h"
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
DE1SOC::DE1SOC() {
	// Open /dev/mem to give access to physical addresses
	this->fd = open( "/dev/mem", (O_RDWR | O_SYNC));
	if (this->fd == -1) {// check for errors in openning /dev/mem
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
    }
    // Get a mapping from physical addresses to virtual addresses
    char* virtual_base = (char*)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, this->fd, LW_BRIDGE_BASE);
    if (virtual_base == MAP_FAILED)	{	// check for errors
        cout << "ERROR: mmap() failed..." << endl;
        close (this->fd); // close memory before exiting
        exit(1); // Returns 1 to the operating system;
    }
    this->pBase=virtual_base;
}

/** Close general-purpose I/O. 
 */ 
DE1SOC::~DE1SOC() {
	if (munmap (this->pBase, LW_BRIDGE_SPAN) != 0) {
        cout << "ERROR: munmap() failed..." << endl;
        exit(1);
    }
    close (this->fd); // close memory
}

/** Write a 4-byte value at the specified general-purpose I/O location. 
 *  @param offset	    Offset where device is mapped. 
 *  @param value	    Value to be written. 
 */ 
void DE1SOC::registerWrite(unsigned int offset, int value) { *(volatile unsigned int*)(this->pBase + offset) = value; }
/** Read a 4-byte value from the specified general-purpose I/O location. 
 *  @param offset	    Offset where device is mapped. 
 *  @return		        Value read. 
 */ 
int DE1SOC::registerRead(unsigned int offset) { return *(volatile unsigned int*)(this->pBase + offset); } 

/** Reads one specific bit of an integer.
 *  @param val      The value to read
 *  @param index    The index of the bit to read
 *  @return         Boolean representing the state of the bit
 */
bool DE1SOC::readBitVal(int val, int index) { return (val & (1 << index)) != 0; }
/** Writes one specific bit of an integer.
 *  @param val      The value to write to
 *  @param index    The index of the bit to write
 *  @param set      Boolean representing the new state of the bit
 *  @return         The updated value
 */
int DE1SOC::setBitVal(int val, int index, bool set) { return (val - (val & (1 << index)) + (set << index)); }
