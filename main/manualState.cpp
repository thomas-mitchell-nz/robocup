/*******************************************************
 *
 * manualstate.cpp
 *
 * Manual state for controlling drive with joystick
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "global.h"
#include "Motor.h"
#include "fsm.h"

/*******************************************************
 * Global variables
 *******************************************************/
int command = COMMAND_NO;
int prevCommand = COMMAND_NO;

/*******************************************************
 * State actions
 *******************************************************/
bool manualInit() { 
  harvester.sweepTowards();
  return true;
}

/*******************************************************/
void manualCleanup() {
  harvester.stop();
}
/*******************************************************/
void manualUpdate() 
{ 
  if (PRINT_STATES) Serial.println("***** MANUAL *****");

  command = joystick.readJoystick();

  if (command == COMMAND_UP && prevCommand != COMMAND_UP) {
    Serial.println("COMMAND UP");
    drive.forward();
  }

  if (command == COMMAND_DOWN && prevCommand != COMMAND_DOWN) {
    Serial.println("COMMAND DOWN");
    drive.reverse();
  }
  
  if (command == COMMAND_LEFT && prevCommand != COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    drive.left();
  }

  if (command == COMMAND_RIGHT && prevCommand != COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    drive.right();
  }
  
  if (command == COMMAND_NO) {
    drive.stop();
  }

  prevCommand = command;
}
