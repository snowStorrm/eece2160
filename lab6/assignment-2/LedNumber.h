#ifndef lednumber_h
#define lednumber_h

// Physical base address of FPGA Devices 
const unsigned int LW_BRIDGE_BASE 	= 0xFF200000;  // Base offset 

// Length of memory-mapped IO window 
const unsigned int LW_BRIDGE_SPAN 	= 0x00005000;  // Address map size

// Cyclone V FPGA device addresses
const unsigned int LEDR_BASE 		= 0x00000000;  // Leds offset 
const unsigned int SW_BASE 			= 0x00000040;  // Switches offset
const unsigned int KEY_BASE 		= 0x00000050;  // Push buttons offset

// Function declarations
char* Initialize(int* fd);
void Finalize(char* pBase, int fd);
void RegisterWrite(char *pBase, unsigned int reg_offset, int value);
int RegisterRead(char *pBase, unsigned int reg_offset);
void WriteAllLeds(char *pBase, int value);

#endif