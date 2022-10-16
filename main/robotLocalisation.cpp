/*******************************************************
 *
 * robotLocalisation.cpp
 *
 * Background task for position tracking
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "robotLocalisation.h"
#include "global.h"

/*******************************************************
 * Local variables
 *******************************************************/
int dist = 0;
int prevDist = 0;
int heading = 0;
int prevHeading = 0;

/*******************************************************
 * Calculates position of robot
 *******************************************************/
void updatePath() 
{
  dist = (abs(leftMotor.getDist())+abs(rightMotor.getDist()))/2;
  heading = odom.getHeading();
  X_POS += (dist-prevDist)*cos(prevHeading*3.14/180);
  Y_POS += (dist-prevDist)*sin(prevHeading*3.14/180);
  GLOBAL_ANGLE = atan2(Y_POS,X_POS)*180/3.14;
  prevDist = dist;
  prevHeading = heading;

  if (PRINT_HEADING) {
    Serial.print("xPos: ");
    Serial.print(X_POS);
    Serial.print("\t");
    Serial.print("yPos: ");
    Serial.print(Y_POS);
    Serial.print("\t");
    Serial.print("Dist: ");
    Serial.println(dist);
    Serial.print("\t");
    Serial.print("Angle: ");
    Serial.println(GLOBAL_ANGLE);
  }
}