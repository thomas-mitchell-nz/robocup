/*******************************************************
 *
 * Colour.cpp
 *
 * Colour sensor class source file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "Colour.h"

Colour::Colour(bool _print) {
  tcs.begin(TCS34725_ADDRESS, &Wire1);
  print = _print;
}

void Colour::check () {
  tcs.getRawData(&red, &green, &blue, &clear); 

  if (print) {
    Serial.print("C:\t"); Serial.print(clear);
    Serial.print("\tR:\t"); Serial.print(red);
    Serial.print("\tG:\t"); Serial.print(green);
    Serial.print("\tB:\t"); Serial.print(blue);
    Serial.println();
  }  
}

bool Colour::isBlue () {
  this->check();
  return ((blue - green) > COLOUR_THRESH);
}

bool Colour::isGreen () {
  this->check();
  return ((green - blue) > COLOUR_THRESH);
}
