/*******************************************************
 *
 * TOF.cpp
 *
 * TOF class source file to poll time-of-flight sensors
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "TOF.h"

TOF::TOF(uint8_t pin, SX1509* _ioPtr, char _name, bool _print) {
  name = _name;
  print = _print;
  xshutPin = pin;  
  ioPtr = _ioPtr;
  this->initWire();
  this->initTOF();
}

int TOF::getRange() {
  return range;
}

void TOF::initTOF() {
  ioPtr->pinMode(xshutPin, OUTPUT);
  ioPtr->digitalWrite(xshutPin, LOW);

  sensor = VL53L1X();

  // Stop driving this sensor's XSHUT low. This should allow the carrier
  // board to pull it high. (We do NOT want to drive XSHUT high since it is
  // not level shifted.) Then wait a bit for the sensor to start up.
  //pinMode(xshutPins[i], INPUT);
  ioPtr->digitalWrite(xshutPin, HIGH);
  delay(10);
  sensor.setTimeout(50);
  sensor.init();
  
  // Each sensor must have its address changed to a unique value other than
  // the default of 0x29 (except for the last one, which could be left at
  // the default). To make it simple, we'll just count up from 0x2A.
  sensor.setAddress(VL53L1X_ADDRESS_START+xshutPin);

  sensor.startContinuous(50);
}

void TOF::initWire() {
  ioPtr->begin(SX1509_ADDRESS);
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C
}

void TOF::updateRange() {
  range = sensor.readRangeContinuousMillimeters()/10;

  if (sensor.timeoutOccurred()) {
    CRITICAL_ERROR = true;
    if (print) Serial.println("***** TIMOUT *****");
    this->initTOF();
  }

  if (print) {
    Serial.print(name);
    Serial.print(" TOF:");
    Serial.println(range);
  }
}