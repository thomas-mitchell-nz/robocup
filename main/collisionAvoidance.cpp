/*******************************************************
 *
 * collisionAvoidance.cpp
 *
 * Collision avoidance system (CAS). Avoids walls and other 
 * obstacles
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "collisionAvoidance.h"
#include "global.h"

/*******************************************************
 * Local variables
 *******************************************************/
unsigned long extraTurnTime = 0;
unsigned long activatedTime = 0;

bool isWallLeft = false;
bool isWallRight = false;
bool isWallAhead = false;

/*******************************************************
* Called regularly - detects and turns away from obstacles
*******************************************************/
void updateCAS (void)
{
  isWallLeft = checkWallLeft();
  isWallRight = checkWallRight();
  isWallAhead = checkWallAhead();

  if (isWallLeft && PRINT_FLAGS) Serial.println("COLLISION LEFT");
  if (isWallRight && PRINT_FLAGS) Serial.println("COLLISION RIGHT");
  if (isWallAhead && PRINT_FLAGS) Serial.println("COLLISION AHEAD");

  if (isWallLeft && !isWallRight && !CAS_ACTIVE) {
    drive.right();
    activatedTime = millis();
    CAS_ACTIVE = true;
  } 
  else if (isWallRight && !isWallLeft && !CAS_ACTIVE) {
    drive.left();
    activatedTime = millis();
    CAS_ACTIVE = true;
  } 
  else if (isWallAhead && !CAS_ACTIVE) {
    random(1,3) == 1 ? drive.left() : drive.right();
    activatedTime = millis();
    CAS_ACTIVE = true;
  }
  
  if (!isWallLeft && !isWallRight && !isWallAhead && CAS_ACTIVE) {
    drive.forward();
    CAS_ACTIVE = false;
    TIME_SINCE_COLLISION = millis();
  }
 }

/*******************************************************
* Check for wall to the left
*******************************************************/
bool checkWallLeft (void)
{
  int switchVal = digitalRead(leftSwitchPin);
  int sonarVal = leftSonar.getRange();
  int TOFval = leftTOF.getRange();
  return switchVal == 0 || sonarVal < SONAR_THRESH || TOFval < BOTTOM_TOF_THRESH;
}

/*******************************************************
* Check for wall to the right
*******************************************************/
bool checkWallRight (void)
{
  int switchVal = digitalRead(rightSwitchPin);
  int sonarVal = rightSonar.getRange();
  int TOFval = rightTOF.getRange();
  return switchVal == 0 || sonarVal < SONAR_THRESH || TOFval < BOTTOM_TOF_THRESH;
}

/*******************************************************
* Check for wall ahead
*******************************************************/
bool checkWallAhead (void)
{
  int TOFval = frontTOF.getRange();
  return TOFval < FRONT_TOF_THRESH && TOFval != 0;
}