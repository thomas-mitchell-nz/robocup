/*******************************************************
 *
 * Harvester.cpp
 *
 * Harvester class class source file to control harvester direction
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "Arduino.h"
#include "Harvester.h"

Harvester::Harvester(int servoPin)
{
  myServo.attach(servoPin);
  myServo.writeMicroseconds(HARVESTER_STOP);
}

void Harvester::sweepTowards(void)
{
  myServo.writeMicroseconds(HARVESTER_FORWARD);
}

void Harvester::sweepAway(void)
{
  myServo.writeMicroseconds(HARVESTER_REVERSE);
}

void Harvester::stop(void)
{
  myServo.writeMicroseconds(HARVESTER_STOP);
}