/*******************************************************
 *
 * Joystick.cpp
 *
 * Joystick class class source file to read joystick commands
 
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>
#include "Joystick.h"

Joystick::Joystick(int _vxPin, int _vyPin, int _swPin, bool _print)
{
  vxPin = _vxPin;
  vyPin = _vyPin;
  swPin = _swPin;
  print = _print;
}

int Joystick::readJoystick(void)
{
  xValue = analogRead(vxPin);
  yValue = analogRead(vyPin);
  
  // converts the analog value to commands
  // reset commands
  command = COMMAND_NO;

  // check left/right commands
  if (xValue < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xValue > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  // check up/down commands
  if (yValue < UP_THRESHOLD)
    command = command | COMMAND_UP;
  else if (yValue > DOWN_THRESHOLD)
    command = command | COMMAND_DOWN;
    
  return command;
}
