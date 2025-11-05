#ifndef DE1SoC_H
#define DE1SoC_H

/**
 * @file   LedCount.cpp
 * @Author John Kimani (j.kimani@northeastern.edu)
 * @date   June, 2025
 * @brief  Process GPIO input and output for the DE1-SoC
 *
 * Contains a LedCount program that opens GPIO ports through 
 * memory-mapping for reading switches and push buttons and 
 * writing to LEDs
 */
 
 // NOTE: Since you may not be working with the DE1 board, most of the 
 // Memory I/O functions have been commented out in this program
 
 // system libraries
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

/* Cyclone V FPGA device addresses */
const unsigned int LW_BRIDGE_BASE 	= 0xFF200000;	// Base offset
const unsigned int LW_BRIDGE_SPAN 	= 0x00005000;	// Address map size
const unsigned int LEDR_BASE 		= 0x00000000;	// Leds offset 
const unsigned int SW_BASE 			= 0x00000040;	// Switches offset
const unsigned int KEY_BASE 		= 0x00000050;	// Push buttons offset

class LEDControl {
  private:
	char *pBase;
	int fd;
	int dummyValue; // for testing without a Zedboard
  public:
	LEDControl();		// Constructor
	~LEDControl();		// Destructor
	void RegisterWrite(unsigned int reg_offset, int value);
	int RegisterRead(unsigned int reg_offset);
	void WriteAllLeds(int value);
};
#endif
