/*******************************************************
 *
 * IMU.cpp
 *
 * IMU class class source file to get odometry 
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/


#include "IMU.h"

IMU::IMU(Adafruit_BNO055* _bnoPtr, bool _print) {
  print = _print;
  bnoPtr = _bnoPtr;
  bnoPtr->begin();
}

int IMU::getHeading() {
  bnoPtr->getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  int heading = orientationData.orientation.x;

  if (print) {
    Serial.print("Current heading: ");
    Serial.println(heading);
  }

  return heading;
}

int IMU::getDesiredHeading(int turnAngle, int dir) {
  int heading = this->getHeading() + turnAngle * dir; // CCW -ve

  if (heading > 360) {
    heading -= 360;
  } 
  else if (heading < 0) {
    heading += 360;
  }

  if (print) {
    Serial.print("Desired heading: ");
    Serial.println(heading);
  }

  return heading;
}

int IMU::getError(int desired) {
  int e = desired-this->getHeading();

  if (abs(e)>180 && e>0) {
    e = abs(e-360);
  } 
  else if (abs(e)>180 && e<0) {
    e = abs(e+360);
  } 
  else {
    e = abs(e);
  }
  
  if (print) {
    Serial.print("Error: ");
    Serial.println(e);
  } 

  return e;
}
