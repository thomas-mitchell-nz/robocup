#ifndef COLOUR_H_
#define COLOUR_H_

/*******************************************************
 *
 * Colour.h
 *
 * Colour sensor class header file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

#define COLOUR_THRESH 150

class Colour {
  public:
    Colour(bool _print=false);
    void check();
    bool isBlue();
    bool isGreen();
    
  private:
    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
    uint16_t clear, red, green, blue;
    bool print;
};

#endif
