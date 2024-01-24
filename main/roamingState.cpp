/*******************************************************
 *
 * roamingState.cpp
 *
 * Randomly bounce around arena in search of weights
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "global.h"
#include "roamingState.h"
#include "fsm.h"

/*******************************************************
 * Local macros and varaibles
 *******************************************************/
#define FORWARD_TIME 10000
#define REVERSE_TIME 2000
#define PICKUP_TIME  3000
#define WEIGHT_RANGE 50
#define DELTA 50

bool reversing = false;
bool wasHome = true;
unsigned long tr = 0;
unsigned long tp = 0;

/*******************************************************
 * State actions
 *******************************************************/
bool roamingInit()
{
  if (!CAStask.isEnabled()) {
    CAStask.enable();
    drive.forward();
    harvester.sweepTowards();
  }

  if (!enemyBaseTask.isEnabled()) {
    enemyBaseTask.enable();
  }

  if (!collectionDetectionTask.isEnabled()) {
    collectionDetectionTask.enable();
  }

  if (!pollSensorsTask.isEnabled()) {
    leftSonar.pulse();
    rightSonar.pulse();
    pollSensorsTask.enable();
  }

  return true;
}

/*******************************************************/
void roamingUpdate() 
{ 
  if (PRINT_STATES) Serial.println("***** ROAMING *****");
  
  if (!CAS_ACTIVE && !FULL && weightLeft() && (millis()-tp)>PICKUP_TIME && (millis()-TIME_SINCE_COLLISION)>2000) {
    if (PRINT_FLAGS) Serial.println("WEIGHT LEFT");
    TURN_ANGLE = SENSOR_ANGLE; // + atan(HALF_WIDTH/sonarVal);
    tp = millis();
    TURN_LEFT = true;
    changeState(&pickUpState);
  }
  else if (!CAS_ACTIVE && !FULL && weightRight() && (millis()-tp)>PICKUP_TIME && (millis()-TIME_SINCE_COLLISION)>2000) {
    if (PRINT_FLAGS) Serial.println("WEIGHT RIGHT");
    TURN_ANGLE = SENSOR_ANGLE; // + atan(HALF_WIDTH/sonarVal);
    tp = millis();
    TURN_RIGHT = true;
    changeState(&pickUpState);
  }

  if (!reversing && (millis()-tr)>FORWARD_TIME) {
    tr = millis();
    harvester.sweepAway();
    if (!CAS_ACTIVE) drive.reverse();
    reversing = true;
  }
  else if (reversing && (millis()-tr)>REVERSE_TIME) {
    if (!FULL) harvester.sweepTowards();
    if (!CAS_ACTIVE) drive.forward();
    reversing = false;
  }

/*
  if (!wasHome && ((HOME_COLOUR == BLUE && colour.isBlue()) || (HOME_COLOUR == GREEN && colour.isGreen()))) {
    wasHome = true;
    changeState(&dropOffState);
  } 
  else if (wasHome && ((HOME_COLOUR == BLUE && !colour.isBlue()) || (HOME_COLOUR == GREEN && !colour.isGreen()))) {
    wasHome = false;
  }  */
}

/*******************************************************/
void roamingCleanup() { }

/*******************************************************
 * Support functions
 *******************************************************/
bool weightLeft() {
  int sonarVal = leftSonar.getRange();
  int TOFval = leftTOF.getRange();
  return TOFval < WEIGHT_RANGE && TOFval != 0 && (sonarVal-TOFval) > DELTA;
}

bool weightRight() {
  int sonarVal = rightSonar.getRange();
  int TOFval = rightTOF.getRange();
  return TOFval < WEIGHT_RANGE && TOFval != 0 && (sonarVal-TOFval) > DELTA;
}