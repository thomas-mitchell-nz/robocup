#ifndef GATE_H_
#define GATE_H_

/*******************************************************
 *
 * Gate.h
 *
 * Gate class class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>
#include <Servo.h>

#define LEFT_OPEN 70
#define RIGHT_OPEN 103
#define LEFT_CLOSE 170
#define RIGHT_CLOSE 3

class Gate {
  public:
    Gate(int leftPin, int rightPin);
    void open();
    void close();
    
  private:
    Servo leftServo, rightServo;
};

#endif