#include "DE1SoC.h"
#include <iostream>
using namespace std;

int main() {
    // instantiate new DE1_SOC instance
    DE1SOC* DE1 = new DE1SOC();
    // loop infinitely
    while (true) {
        int a;
        // get user input
        cout << "Please input an angle to set the servo to (0 - 180). Enter -1 to quit: ";
        cin >> a;
        // if input is -1, quit program
        if (a == -1) break;
        // clamping function between 0 and 180 degrees
        a = (a < 0) ? 0 : (a > 180) ? 180 : a;
        // set the register holding the angle value
        DE1->registerWrite(PIO_BASE, a);
    }
}