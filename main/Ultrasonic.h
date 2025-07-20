#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*******************************************************
 *
 * Ultrasonic.h
 *
 * Ultrasonic class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>

class Ultrasonic {
  public:
    Ultrasonic(int trigger, int echo, int max_dist=200, bool print=false);
    void updateRange();
    void pulse();
    void echo();
    bool isFinished(){ return _finished; }
    unsigned int getRange();
    
  private:
    int _trigger, _echo, _int, _max, _time, _range;
    volatile unsigned long _start, _end;
    volatile bool _finished;
    bool _print;
};

#endif
