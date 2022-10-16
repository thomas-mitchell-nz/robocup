/*******************************************************
 *
 * Gate.cpp
 *
 * Gate class class source file to open and close gate
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "Gate.h"

Gate::Gate(int leftPin, int rightPin) {
  leftServo.attach(leftPin);
  rightServo.attach(rightPin);
  leftServo.write(LEFT_CLOSE);
  rightServo.write(RIGHT_CLOSE);
}

void Gate::close ()
{
  leftServo.write(LEFT_CLOSE);
  rightServo.write(RIGHT_CLOSE);
}

void Gate::open ()
{
  leftServo.write(LEFT_OPEN);
  rightServo.write(RIGHT_OPEN);
}