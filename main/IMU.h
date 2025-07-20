#ifndef IMU_H_
#define IMU_H_

/*******************************************************
 *
 * IMU.h
 *
 * IMU class class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#define CW  1
#define CCW -1

class IMU {
  public:
    IMU(Adafruit_BNO055* _bnoPtr, bool _print=false);
    int getHeading();
    int getDesiredHeading(int turnAngle, int dir);
    int getError(int desired);

  private:
    sensors_event_t orientationData;
    Adafruit_BNO055* bnoPtr;
    bool print;
};

#endif
