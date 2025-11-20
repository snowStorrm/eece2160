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
#include "SpiderLeg.h"
#include "LEDControl.h"

using namespace std;

int main(int argc, char *argv[]){
	// Take in animation speed as argument
	int motorSpd = atoi(argv[1]);

	cout << "\nProgram Starting...!" << endl; 
	// Create necessary class objects including leg with specified motor indices
	MMap *m_map = new MMap();
	LEDControl *pio = new LEDControl(m_map);
	SpiderLeg* leg = new SpiderLeg(m_map, 9, 10 ,11);

	// Ensure the leg is at its default position and set its speed to what was specified on startup
	leg->Reset();
	leg->SetSpeed(SpiderLeg::Hip, motorSpd);
	leg->SetSpeed(SpiderLeg::Knee, motorSpd);
	leg->SetSpeed(SpiderLeg::Ankle, motorSpd);

	// Loop the movements infinitely. User can exit by pressing CTRL+C in terminal
	while (true) {
		// Wait until current move operation has finished
		while (!leg->IsReady()) sleep(0.001);
		// Wait a moment before continuing
		sleep(0.25);
		// Lift leg
		leg->MoveJoint(SpiderLeg::Knee, -30.);
		leg->MoveJoint(SpiderLeg::Ankle, -30.);
		// Wait until current move operation has finished
		while (!leg->IsReady()) sleep(0.001);
		// Wait a moment before continuing
		sleep(0.25);
		// Rotate leg forward
		leg->MoveJoint(SpiderLeg::Hip, 30.);
		// Wait until current move operation has finished
		while (!leg->IsReady()) sleep(0.001);
		// Wait a moment before continuing
		sleep(0.25);
		// Lower leg
		leg->MoveJoint(SpiderLeg::Knee, 30.);
		leg->MoveJoint(SpiderLeg::Ankle, 30.);
		// Wait until current move operation has finished
		while (!leg->IsReady()) sleep(0.001);
		// Wait a moment before continuing
		sleep(0.25);
		// Push off ground to move forward
		leg->MoveJoint(SpiderLeg::Hip, -30.);
	}
	// detele dynamic objects
	delete leg;
	delete pio;		
	delete m_map;
	cout << "Terminating..." << endl;
	return 0;
}	
