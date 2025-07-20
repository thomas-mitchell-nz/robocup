#ifndef DRIVE_H_
#define DRIVE_H_

/*******************************************************
 *
 * Drive.h
 *
 * Drive class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "Arduino.h"

class Drive {
  public:
    Drive();
    void forward (void);
    void reverse (void);
    void right (void);
    void left (void);
    void stop (void);
};

#endif
