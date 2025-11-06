#ifndef de1soc_h
#define de1soc_h

// Physical base address of FPGA Devices 
const unsigned int LW_BRIDGE_BASE 	= 0xFF200000;  // Base offset 

// Length of memory-mapped IO window 
const unsigned int LW_BRIDGE_SPAN 	= 0x00005000;  // Address map size

// Cyclone V FPGA device addresses
const unsigned int LEDR_BASE 		= 0x00000000;  // Leds offset 
const unsigned int SW_BASE 			= 0x00000040;  // Switches offset
const unsigned int KEY_BASE 		= 0x00000050;  // Push buttons offset

// DE1-SoC declaration class
class DE1SOC {
    private:
        int fd;
    public:
        char* pBase;
        // constructor/destructor
        // this is where initialize() and finalize() will be executed
        DE1SOC();
        ~DE1SOC();
        // memory read/write
        void registerWrite(int offset, int val);
        int registerRead(int offset);
};

// Function declarations

// bit value reading
bool readBitVal(int val, int index);
int setBitVal(int val, int index, bool set);

// input reading
bool readSwitch(DE1SOC* board, int swIdx);
int readAllSwitches(DE1SOC* board);
int getButtonPressed(DE1SOC* board);

// LED writing
void writeLED(DE1SOC* board, int LEDIdx, bool state);
void writeAllLEDs(DE1SOC* board, int value);

#endif