/*******************************************************
 *
 * Drive.cpp
 *
 * Drive class source file for forward, reverse, left, right commands
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/


#include "Arduino.h"
#include "Drive.h"
#include "global.h"
#include "Motor.h"

/*******************************************************
* Class constructor
*******************************************************/
Drive::Drive() {}

/*******************************************************
* Turn left
*******************************************************/
void Drive::left (void)
{
  //leftMotor.updateTarget(CRUISING_RPM,REVERSE);
  //rightMotor.updateTarget(CRUISING_RPM,FORWARD);
  leftMotor.updatePulse(REVERSE);
  rightMotor.updatePulse(FORWARD);
}

/*******************************************************
* Turn right
*******************************************************/
void Drive::right (void)
{
  //leftMotor.updateTarget(CRUISING_RPM,FORWARD);
  //rightMotor.updateTarget(CRUISING_RPM,REVERSE);
  leftMotor.updatePulse(FORWARD);
  rightMotor.updatePulse(REVERSE);
}

/*******************************************************
* Fast forward
*******************************************************/
void Drive::forward (void)
{
  //leftMotor.updateTarget(CRUISING_RPM, FORWARD);
  //rightMotor.updateTarget(CRUISING_RPM, FORWARD);
  leftMotor.updatePulse(FORWARD);
  rightMotor.updatePulse(FORWARD);
}

/*******************************************************
* Fast reverse
*******************************************************/
void Drive::reverse (void)
{
  //leftMotor.updateTarget(CRUISING_RPM, REVERSE);
  //rightMotor.updateTarget(CRUISING_RPM, REVERSE);
  leftMotor.updatePulse(REVERSE);
  rightMotor.updatePulse(REVERSE);
}

/*******************************************************
* Stop
*******************************************************/
void Drive::stop (void)
{
  //leftMotor.updateTarget(0, STOP);
  //rightMotor.updateTarget(0, STOP);
  leftMotor.updatePulse(STOP);
  rightMotor.updatePulse(STOP);
}
