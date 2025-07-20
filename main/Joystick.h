#ifndef JOYSTICK_H_
#define JOYSTICK_H_

/*******************************************************
 *
 * Joystick.h 
 * 
 * Joystick class header file
 *
 * Authors: T.J. Mitchell
 * Last modified:  17/10/22
 *
 *******************************************************/

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

#include "Arduino.h"

class Joystick {
  public:
    Joystick(int vxPin, int vyPin, int swPin, bool _print=false);
    int readJoystick(void);

  private:
    int xValue = 0; // To store value of the X axis
    int yValue = 0; // To store value of the Y axis
    int command = COMMAND_NO;
    bool print;
    int vxPin;
    int vyPin;
    int swPin; 
};

#endif 
