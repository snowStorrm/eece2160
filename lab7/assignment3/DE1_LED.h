#ifndef de1_led_h
#define de1_led_h

// include superclass
#include "DE1SoC.h"

// DE1_LED inherits DE1SOC superclass
class DE1_LED: public DE1SOC {
    public:
        unsigned int reg;
        // input reading
        bool readSwitch(int swIdx);
        int readAllSwitches();
        int getButtonPressed();

        // LED writing
        void writeLED(int LEDIdx, bool state);
        void writeAllLEDs(int value);
};

#endif