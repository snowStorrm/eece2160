/**
 * @file   Main.cpp
 * @brief  Tests the Spider robot rc servo movements
 */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include "MMap.h"
#include "Motor.h"
#include "LEDControl.h"

using namespace std;

int main(int argc, char *argv[]){
	// Take in motor index AND motor speed as executable parameters
	int motorIdx = atoi(argv[1]);
	int motorSpd = atoi(argv[2]);

	cout << "\nProgram Starting...!" << endl; 
	// Create necessary class objects including motor specified on startup
	MMap *m_map = new MMap();
	LEDControl *pio = new LEDControl(m_map);
    Motor *motor = new Motor(m_map, motorIdx);

	// Ensure the motor is at its default angle and set its speed to what was specified on startup
	motor->Reset();
	motor->SetSpeed(motorSpd);

	// Create angle variable as well as variables to track button presses
	float angle = 0.;
	int currBtn = 0, prevBtn = 0;
	// Repeat infinitely, user can exit by pressing CTRL+C in terminal
	while (true) {
		// Read each button and return which one is pressed. If both pressed, do not update. If none pressed, return -1
		currBtn = (pio->ReadButton(0)) ? 0 : (pio->ReadButton(1)) ? 1 : (!pio->ReadButton(0) && !pio->ReadButton(1)) ? -1 : currBtn;
		// If button pressed is different AND at least one button is pressed, change the angle
		if (currBtn != prevBtn && currBtn != -1) {
			// If KEY0, decrease angle by 15 degrees. If KEY1, increase angle by 15 degrees
			angle += (currBtn == 0) ? -15. : (currBtn == 1) ? 15. : 0.;
			// Clamp angle between minimum and maximum
			angle = (angle > DEGREE_MAX) ? DEGREE_MAX : (angle < DEGREE_MIN) ? DEGREE_MIN : angle;
			// Move the motor to that angle
			motor->Move(angle);
		}
		// Set previous button and repeat after a delay
		prevBtn = currBtn;
		sleep(0.001);
	}
	// detele dynamic objects
	delete motor;
	delete pio;		
	delete m_map;
	cout << "Terminating..." << endl;
	return 0;
}	
