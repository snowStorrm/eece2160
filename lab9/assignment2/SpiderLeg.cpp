 /**
 * @file   SpiderLeg.cpp
 * @Author Richard, Modified by: John Kimani (j.kimani@northeastern.edu)
 * @date   Modified on: 11/01/2025
 * @brief  Process a spider leg with 3 joints: Hip, Knee, and Ankle
 *
 * Contains a SpiderLeg class that provides functions to operate
 * on the various legs on the Terasic Spider robot
 */
#include <cassert>
#include "SpiderLeg.h"

/**
 *  Constructor initializes 3 dynamic motor objects for the Leg
 */
SpiderLeg::SpiderLeg(MMap* mmio, int hipID,int kneeID,int ankleID) {
	m_szMotor[Hip] = new Motor(mmio, hipID);
	m_szMotor[Knee] = new Motor(mmio, kneeID);
	m_szMotor[Ankle] = new Motor(mmio, ankleID);
}

/**
 * Delete the 3 dynamic motor objects for the Leg
 */
SpiderLeg::~SpiderLeg() {
	for(int i=0;i<JOINT_NUM;i++){
		delete m_szMotor[i];
	}
}

/**
 * Reset the 3 joints on the Leg
 */
void SpiderLeg::Reset(void) {
	m_szMotor[Hip]->Reset();
	m_szMotor[Knee]->Reset();
	m_szMotor[Ankle]->Reset();
}

/**
 * Move the specified joint to the specified angle
 */
void SpiderLeg::MoveJoint(JOINT_ID JointID, float fAngle) {
	m_szMotor[JointID]->Move(fAngle);
}

/**
 *  Check if all the joints on the Leg are ready
 */
bool SpiderLeg::IsReady(void) {
	return (m_szMotor[Hip]->IsReady() && m_szMotor[Knee]->IsReady() && m_szMotor[Ankle]->IsReady());
}

/**
 *  Get the angle for the specified joint
 */
float SpiderLeg::GetfAngle(JOINT_ID JointID) {
	return m_szMotor[JointID]->GetfAngle();
}

/**
 *  Set the speed for the specified joint
 */
void SpiderLeg::SetSpeed(JOINT_ID JointID, int Speed) {
	m_szMotor[JointID]->SetSpeed(Speed);
}

/**
 *  Return the speed for the specified joint
 */
uint32_t SpiderLeg::GetSpeed(JOINT_ID JointID)
{
	return m_szMotor[JointID]->GetSpeed();
}

