#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include "DE1SoC.h"
using namespace std;


/**
 * Initialize general-purpose I/O
 *  - Opens access to physical memory /dev/mem
 *  - Maps memory at offset into virtual address space
 *
 * @param  fd	File descriptor passed by reference, where the result
 *		of function 'open' will be stored.
 * @return	Address to virtual memory which is mapped to physical,
 *          	or MAP_FAILED on error.
 */
LEDControl::LEDControl()
{
	cout << "\nStarting...." << endl;
	dummyValue = 0;
	char dummyChar;
	pBase = &dummyChar;
	
/* 	// Open /dev/mem to give access to physical addresses
	fd = open( "/dev/mem", (O_RDWR | O_SYNC));
	if (fd == -1)		//  check for errors in openning /dev/mem
	{
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
	}
	
   // Get a mapping from physical addresses to virtual addresses
   pBase = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE); */
   if (pBase == MAP_FAILED)		// check for errors
   {
      cout << "ERROR: mmap() failed..." << endl;
      //close (fd);		// close memory before exiting
      exit(1);
   }
}

/**
 * Close general-purpose I/O.
 *
 * @param pBase	Virtual address where I/O was mapped.
 * @param fd	File descriptor previously returned by 'open'.
 * Close the previously-opened virtual address mapping
 * Close /dev/mem to give access to physical addresses
 */
LEDControl::~LEDControl()
{
	if (dummyValue < 0)
	//if (munmap (pBase, LW_BRIDGE_SPAN) != 0)
	{
      cout << "ERROR: munmap() failed..." << endl;
      exit(1);
	}
   close (fd); 	// close memory
   cout << "\nTerminating...." << endl;
}

/**
 * Write a 4-byte value at the specified general-purpose I/O location.
 *
 * @param pBase		Base address returned by 'mmap'.
 * @parem reg_offset	Offset where device is mapped.
 * @param value		Value to be written.
 */
void LEDControl::RegisterWrite(unsigned int reg_offset, int value)
{
	//* (volatile unsigned int *)(pBase + reg_offset) = value;
	dummyValue = value;
}

/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * @param pBase		Base address returned by 'mmap'.
 * @param reg_offset	Offset where device is mapped.
 * @return		Value read.
 */
int LEDControl::RegisterRead(unsigned int reg_offset)
{
	//return * (volatile unsigned int *)(pBase + reg_offset);
	return dummyValue;
}

/**
 * Show the input integer value on LEDs
 *
 * - Calls RegisterWrite to set all LEDs 
 * @param value	Value to show on LEDs
 */
void LEDControl::WriteAllLeds(int value)
{
	cout << "\nWriting to LEDs...." << endl;
	for(int i = 0; i < 10; i++) {// write to all LEDs
		cout << "LED " << i << " state: " << ((value / (1<<i)) % 2) << endl;
	}
   //RegisterWrite(pBase, LEDR_BASE, value);
}