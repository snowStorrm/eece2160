#include "DE1SoC.h"
#include <iostream>
using namespace std;

int main() {
    DE1SOC* DE1 = new DE1SOC();
    while (true) {
        int a;
        cout << "Please input an angle to set the servo to (0 - 180). Enter -1 to quit: ";
        cin >> a;
        if (a == -1) break;
        a = (a < 0) ? 0 : (a > 180) ? 180 : a;
        DE1->registerWrite(PIO_BASE, a);
    }
}