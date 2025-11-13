#include <iostream>
#include "DE1SoC.h"
#include "DE1_HEX.h"
#include <string>
#include <unistd.h>
using namespace std;

int main() {
    // create new HEX controller
    DE1_HEX* hex = new DE1_HEX();
    // loop 50 times, starting from -25
    for (int i = -25; i <= 25; i++) {
        // write i^3 to the hex display
        int value = i*i*i;
        cout << "Counter value: " << value << endl;
        hex->setAll(to_string(value));
        // wait 1 second between iterations
        sleep(1);
    }
    // destroy HEX controller
    hex->~DE1_HEX();
}