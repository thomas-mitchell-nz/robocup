#ifndef TOF_H_
#define TOF_H_

/*******************************************************
 *
 * TOF.h
 *
 * TOF class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <SparkFunSX1509.h>

#define VL53L1X_ADDRESS_START 0x30

class TOF {
  public:
    TOF(uint8_t pin, SX1509* ioPtr, char _name, bool _print=false);
    int getRange();
    void updateRange();
    void initWire();
    void initTOF();
    
  private:
    static const byte SX1509_ADDRESS = 0x3F;
    bool print, CRITICAL_ERROR = false;
    uint8_t xshutPin;
    VL53L1X sensor;
    SX1509* ioPtr;
    char name;
    int range;   
};

#endif
