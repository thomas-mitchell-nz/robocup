#ifndef Harvester_h
#define Harvester_h

/*******************************************************
 *
 * Harvester.h
 *
 * Harvester class class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/


#include "Arduino.h"
#include <Servo.h>

#define HARVESTER_FORWARD 1950
#define HARVESTER_REVERSE 1150
#define HARVESTER_STOP 1500

class Harvester {
  public:
    Harvester(int servoPin);
    void sweepTowards(void);
    void sweepAway(void);
    void stop(void);
    
  private:
    Servo myServo;
};

#endif
