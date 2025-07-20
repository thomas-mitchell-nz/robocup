/*******************************************************
 *
 * LoadCell.cpp
 *
 * LoadCell class class source file to read load cell strain
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "LoadCell.h"

LoadCell::LoadCell(HX711_ADC* _cellPtr, bool _print) {
  print = _print;
  cellPtr = _cellPtr;
  cellPtr->begin();
  cellPtr->start(stabilizingtime, _tare);
  cellPtr->setCalFactor(CALIBRATION_VALUE); // set calibration value (float)
}

void LoadCell::dataReadyISR() {
  if (cellPtr->update()) {
    if (millis() > t + serialPrintInterval) {
      weight = cellPtr->getData();
      newDataReady = 0;
      t = millis();

      if (print) {
        Serial.print("Load: ");
        Serial.println(weight);
      }
    }
  }

  // receive command from serial terminal, send 't' to initiate tare operation:
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') cellPtr->tareNoDelay();
  }
}

int LoadCell::getWeight() {
  return weight;
}