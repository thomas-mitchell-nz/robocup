#ifndef Motor_h
#define Motor_h

/*******************************************************
 *
 * Motor.h 
 * 
 * Motor class header file
 *
 * Authors: T.J. Mitchell
 * Last modified:  17/10/22
 *
 *******************************************************/

#include "Arduino.h" 
#include <Servo.h>

#define MOTOR_PERIOD  300
#define ENCODER_RES   663 // encoder resolution 
#define DIAMETER      62.33

#define FORWARD  1025
#define REVERSE  1975
#define STOP     1500

class Motor {
  public:
    Motor(int _motorPin, int ENCA, int ENCB, bool _print=false); // class constructor
    void updateTarget(int target, int initial); // set target rpm 
    void updateMotor(void); // closed loop control for motors
    void readEncoder(void); // read encoder value
    int getDist(void);
    void updatePulse(int pulse);

  private:
    int targetRPM;
    int motorRPM;
    int motorDir;
    int motorPulse;
    int encoderVal;
    int motorPin;
    int encoderA;
    int encoderB;
    int motorDist;  
    Servo motor;
    bool print; 
    bool updateMotorFlag=true;
};

#endif
