/*******************************************************
 *
 * Ultrasonic.cpp
 *
 * Ultrasonic class source file to poll ultrasonic sensors
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trigger, int echo, int max_dist, bool print) {
  _trigger = trigger;
  _echo = echo;
  _max = max_dist;
  _finished = false;
  _print = print;
  
  pinMode(_trigger, OUTPUT);
  digitalWrite(_trigger, LOW);
  pinMode(_echo, INPUT);
}

void Ultrasonic::pulse() {
  _finished=false;
  digitalWrite(_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigger, LOW); 
}

unsigned int Ultrasonic::getRange(){
  return _range;
}

void Ultrasonic::echo(){
  switch(digitalRead(_echo)){
    case HIGH:
      _start=micros();
      break;
    case LOW:
      _end=micros();
      _finished=true;
      break;
  }   
}

void Ultrasonic::updateRange(){
  _time = _end-_start;
  _range = _time/58;
  if (_time > 2*_max/0.0343 || _range == 0) {
    _range = 200;
  }
  if (_print) {
    Serial.print("Sonar ");
    Serial.print(_trigger);
    Serial.print(": ");
    Serial.println(_range);
  }
}