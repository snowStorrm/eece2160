#include "DE1SoC.h"
#include <iostream>
using namespace std;

/**
 * Operates the PYNQ LEDs and switches
 */
int main()
{
	// Initialize
	LEDControl *de1 = new LEDControl();	
	
	// Sample test program
	int value = 0; 
	cout << "Enter an int value between 0 to 1023: "; 
	cin >> value; 
	cout << "value to be written to LEDs = " << value << endl; 
	de1->WriteAllLeds(value);

	delete de1;
	// Done
}