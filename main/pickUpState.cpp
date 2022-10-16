/*******************************************************
 *
 * pickUpState.cpp
 *
 * Seek and pick up weight
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "global.h"
#include "pickUpState.h"
#include "fsm.h"
#include "IMU.h"

/*******************************************************
 * Local macros and varaibles
 *******************************************************/
#define PICK_UP_WATCHDOG 5000

bool drivingForward = false;
int weightHeading;
int prevNumWeights;
unsigned long t;

/*******************************************************
 * State actions
 *******************************************************/
bool pickUpInit()
{ 
  prevNumWeights = NUM_WEIGHTS;
  t = millis();

  if (TURN_LEFT && !CAS_ACTIVE) {
    weightHeading = odom.getDesiredHeading(TURN_ANGLE,CCW);
    if (!CAS_ACTIVE) drive.left();
  }
  else if (TURN_RIGHT && !CAS_ACTIVE) {
    weightHeading = odom.getDesiredHeading(TURN_ANGLE,CW);
    if (!CAS_ACTIVE) drive.right();
  }

  return true;
}

/*******************************************************/
void pickUpUpdate() 
{ 
  if (PRINT_STATES) Serial.println("***** PICK UP *****");

  if (!drivingForward && odom.getError(weightHeading) < ERROR_TOL) {
    drivingForward = true;
    if (!CAS_ACTIVE) drive.forward();
  }

  if (CAS_ACTIVE || NUM_WEIGHTS > prevNumWeights || (millis()-t)>PICK_UP_WATCHDOG) {
    if (!CAS_ACTIVE) drive.forward();
    changeState(&roamingState);
  }
}

/*******************************************************/
void pickUpCleanup()
{
  TURN_ANGLE = 0;
  TURN_LEFT = false;
  TURN_RIGHT = false;
  drivingForward = false;
}