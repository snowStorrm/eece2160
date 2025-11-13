#ifndef de1_hex_h
#define de1_hex_h

// need DE1SoC.h included since we're using it as a superclass
#include "DE1SoC.h"
#include <string>
using namespace std;


// Hex display class inherits the base functionality of the DE1SOC superclass
class DE1_HEX: public DE1SOC {
    private:
        // reg0 holds values for HEX3, HEX2, HEX1, and HEX0 
        // reg1 holds values for HEX5 and HEX4
        unsigned int reg0, reg1;
    public:
        // we aren't constructing anything beyond what the superclass needs, so we only need a special destructor function
        ~DE1_HEX();

        // function declarations
        void clearAll();
        void clear(int);
        void setAll(string);
        void set(int, char);
};

#endif