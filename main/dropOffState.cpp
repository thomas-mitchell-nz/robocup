/*******************************************************
 *
 * dropOffState.cpp
 *
 * Drop off weights
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "global.h"
#include "dropOffState.h"
#include "fsm.h"

/*******************************************************
 * Local macros and varaibles
 *******************************************************/
#define DROP_OFF_WATCHDOG 10000
bool turning = false;
bool gateOpen = false;
unsigned long td = 0;
int dropOffHeading;

/*******************************************************
 * State actions
 *******************************************************/
bool dropOffInit()
{ 
  CAStask.disable();
  drive.forward();
  td = millis();
  return true;
}

/*******************************************************/
void dropOffCleanup() {}

/*******************************************************/
void dropOffUpdate() 
{ 
  if (PRINT_STATES) Serial.println("***** DROP OFF *****");
  
  if (!turning && !gateOpen && (millis()-td) > 500) {
    drive.right();
    td = millis();
    turning = true;
  }
  
  if (turning && !gateOpen && (millis()-td) > 2000) {
    turning = false;
    td = millis();
    gate.open();
    gateOpen = true;
    drive.stop();
  }

  if ((millis()-td)>DROP_OFF_WATCHDOG || (gateOpen && (millis()-td)>3000)) {
    CAStask.enable();
    drive.forward();
    gate.close();
    gateOpen = false;
    changeState(&roamingState);
  }
}