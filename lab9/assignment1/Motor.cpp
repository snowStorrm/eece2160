 /**
 * @file   Motor.cpp
 * @Author Richard, Modified by: John Kimani (j.kimani@northeastern.edu)
 * @date   Modified on: 11/01/2025
 * @brief  Process an RC Serco motor in the Terasic Spider
 *
 * Implements the Motor class that provides functions to operate
 * on the various rc servos on the Terasic Spider robot
 */
 
#include "Motor.h"
#include "RegisterMap.h"
#include <math.h>
#include <iostream>
#include <unistd.h>
using namespace std;

/*
*	Constructor initializes the specified servo
*	with defualt values
*/
Motor::Motor(MMap* mio, int MonotrID)
{
	m_nMotorID = MonotrID;		// Motor ID (0-17) specifies rc servo to test
	motor_angle = 0.0;			// Angle [-90 to 90] degrees. 0.0 is the defualt
	motor_speed = DELAY_MAX; 	// Actual delay in cycles. Higher delay ==> slow speed
	mmio = mio;					// Memory map object for register access
	
	uint32_t duty_cycle = 75000;	// Neutral 0.0 degrees
	// 	Setup the PWM period, default (duty cycle=75000), default speed=1700 cycles
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_TOTAL_DUR), PWM_PERIOD);
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_HIGH_DUR), duty_cycle);
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ADJ_SPEED), motor_speed);
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ABORT), 0);	// wake up mode
}

/**
*	Destructor
*/
Motor::~Motor() {
	// Stop sending PWM
	mmio->RegisterWrite((szPWM_Base[m_nMotorID] + REG_ABORT), 1);	// Disable PWM signal
}

/**
 * Puts the motor into the neutral, angle 0 position by
 * calling the specific function Move(...).
 */
void Motor::Reset(void) {
	this->Move(0.);
}

/**
 * @return true when this motor is prepared to receive
 * a new SetSpeed or Move method call; otherwise false.
*/
bool Motor::IsReady(void) {
	// Bit mask the speed register with a constant 1. If ready, this masked value will equal 1.
	return (mmio->RegisterRead(szPWM_Base[this->m_nMotorID] + REG_ADJ_STATUS) & 1 == 1);
}

/**
 *	Check the current motor angle
 */
float Motor::GetfAngle(void) {
	return this->motor_angle;
}

/**
 * Compute an appropriate delay value based on the given speed.
 * @param speed - a number between SPEED_MIN and SPEED_MAX,
 * Limit the angle to SPEED_MAX or SPEED_MIN if out of bounds
 * Compute motor_speed with your algorithm before writing to register
 */
void Motor::SetSpeed(int speed) {
	// Clamp the speed between its minimum and maximum
	int clampedSpeed = (speed > SPEED_MAX) ? SPEED_MAX : (speed < SPEED_MIN) ? SPEED_MIN : speed;
	this->motor_speed = clampedSpeed;
	// Compute PWM width in clock cycles and write to register
	uint32_t pwmTime = (SPEED_MAX - (speed - SPEED_MIN)) * 700 / (SPEED_MAX - SPEED_MIN) + 1000;
	this->mmio->RegisterWrite(szPWM_Base[this->m_nMotorID] + REG_ADJ_SPEED, pwmTime);
}

/**
 *	Return the current motor speed
 */
uint32_t Motor::GetSpeed(void) {
	return this->motor_speed;
}

/**
 *	Move motor to the specified angle. First...
 * @param fAngle - a number between DEGREE_MIN and DEGREE_MAX,
 *  Limit the angle to DEGREE_MAX or DEGREE_MIN if out of bounds
 *  If angle = -0.0 then set it to 0.0
 *  If controlling right side motors, set fAngle = -fAngle
 *  Compute PWM duty cycle with your algorithm before writing to register
 */
void Motor::Move(float fAngle) {
	// Wait until the motor is finished moving
	while (!this->IsReady()) sleep(0.001);
	// Clamp the angle between its minimum and maximum
	float clampedAngle = (fAngle > DEGREE_MAX) ? DEGREE_MAX : (fAngle < DEGREE_MIN) ? DEGREE_MIN : fAngle;
	// Flip angle for right side motors
	if (clampedAngle == -0. || this->m_nMotorID <= 8) clampedAngle *= -1.;
	// Set this Motor object's target angle property
	this->motor_angle = clampedAngle;
	// Compute PWM width in clock cycles and write to register
	uint32_t pwmTime = (clampedAngle - (float)DEGREE_MIN) * 100000. / (float)(DEGREE_MAX - DEGREE_MIN) + 25000.;
	this->mmio->RegisterWrite(szPWM_Base[this->m_nMotorID] + REG_HIGH_DUR, pwmTime);
}
