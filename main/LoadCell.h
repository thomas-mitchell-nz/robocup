#ifndef LOADCELL_H_
#define LOADCELL_H_

/*******************************************************
 *
 * LoadCell.h
 *
 * LoadCell class class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>
#include <HX711_ADC.h>
#include <EEPROM.h>

#define CALIBRATION_VALUE 696

class LoadCell {
  public:
    LoadCell(HX711_ADC* _cellPtr, bool _print=false);
    void dataReadyISR();
    int getWeight();

  private:
    bool print;
    HX711_ADC* cellPtr;
    const int calVal_eepromAdress = 0;
    unsigned long t = 0;
    volatile boolean newDataReady;
    unsigned long stabilizingtime = 2000; // tare preciscion can be improved by adding a few seconds of stabilizing time
    bool _tare = true; // set this to false if you don't want tare to be performed
    const int serialPrintInterval = 0; //increase value to slow down serial print activity
    float weight;
};

#endif
