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
const unsigned int HEX3_HEX0_BASE   = 0x00000020;  // HEX3 to HEX0 offset
const unsigned int HEX5_HEX4_BASE   = 0x00000030;  // HEX5 to HEX4 offset
const unsigned int PIO_BASE         = 0x00000020;  // Parallel I/O offset

// DE1-SoC declaration class
class DE1SOC {
    private:
        int fd;
        char* pBase;
    public:
        // constructor/destructor
        // this is where initialize() and finalize() will be executed
        DE1SOC();
        ~DE1SOC();
        // memory read/write
        void registerWrite(unsigned int offset, int val);
        int registerRead(unsigned int offset);
        // Function declarations

        // bit value reading
        bool readBitVal(int val, int index);
        int setBitVal(int val, int index, bool set);
};



#endif