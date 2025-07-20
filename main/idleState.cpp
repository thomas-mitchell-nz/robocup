/*******************************************************
 *
 * idleState.cpp
 *
 * Wait until go button is pressed
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>
#include "global.h"
#include "idleState.h"
#include "fsm.h"

/*******************************************************
 * State actions
 *******************************************************/
bool idleInit()
{ 
  CAStask.disable();
  harvester.stop();
  drive.stop();
  gate.close();
  return true;
}
/*******************************************************/
void idleUpdate() 
{ 
  if (PRINT_STATES) Serial.println("***** IDLE *****");

  if (digitalRead(goButtonPin)) {
    HOME_COLOUR = colour.isBlue() ? BLUE : GREEN;
    drive.forward();
    changeState(&roamingState);
  }
}
/*******************************************************/
void idleCleanup() {}