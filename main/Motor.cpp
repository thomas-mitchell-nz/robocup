/*******************************************************
 *
 * Motor.cpp
 * 
 * Motor class source file to enable motor and encoder functionality
 *
 * Authors: T.J. Mitchell
 * Last modified:  17/10/22
 *
 *******************************************************/

#include "Arduino.h" 
#include "Motor.h"

Motor::Motor(int _motorPin, int ENCA, int ENCB, bool _print)
{
  motorPin = _motorPin;
  encoderA = ENCA;
  encoderB = ENCB;
  print = _print;
  
  motor.attach(motorPin);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  motor.writeMicroseconds(STOP);
}

void Motor::updateTarget(int rpm, int initial) 
{
  updateMotorFlag = true;
  targetRPM = rpm;
  motorPulse = initial;
  motor.writeMicroseconds(motorPulse);
}

void Motor::updatePulse(int pulse) 
{
  updateMotorFlag = false;
  motor.writeMicroseconds(pulse);
}

void Motor::updateMotor(void) 
{
  motorRPM = encoderVal*60000.0/ENCODER_RES/MOTOR_PERIOD; // 60000 ms per minute
  motorDist += 3.14*DIAMETER*encoderVal*motorDir/ENCODER_RES;
  if (motorRPM < targetRPM && motorRPM > 0 && motorPulse < 1990 && motorPulse > 1010 && updateMotorFlag) {
    motorPulse += motorDir;
    motor.writeMicroseconds(motorPulse);
  } else if (motorRPM > targetRPM && motorRPM > 0 && motorPulse < 1990 && motorPulse > 1010 && updateMotorFlag) {
    motorPulse -= motorDir;
    motor.writeMicroseconds(motorPulse);
  }

  if (print && motorRPM > 0) {
    Serial.print("MTR: ");
    Serial.print(motorPin);     
    Serial.print(", ENC: ");
    Serial.print(encoderVal);
    Serial.print(", DIR: ");      
    Serial.print(motorDir);
    Serial.print(", RPM: ");
    Serial.print(motorRPM);
    Serial.print(", TARGET: ");
    Serial.print(targetRPM);
    Serial.print(", PULSE: ");
    Serial.print(motorPulse); 
    Serial.print(", DIST: ");
    Serial.println(motorDist);     
  }

  encoderVal = 0; // clear encoder value
}

void Motor::readEncoder(void)
{
  int val = digitalRead(encoderB);

  if (val > 0) {
    motorDir = 1;
  } else {
    motorDir = -1;
  }
  
  encoderVal++;
}

int Motor::getDist() {
  return motorDist;
}
