/*******************************************************
 *
 * main.ino
 * 
 * Main project file
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "Arduino.h" 
#include "Drive.h"
#include "Motor.h"
#include "Joystick.h"
#include "Harvester.h"
#include "global.h"
#include "Ultrasonic.h"
#include "manualState.h"
#include "roamingState.h"
#include "dropOffState.h"
#include "idleState.h"
#include "pickUpState.h"
#include "Colour.h"
#include "fsm.h"
#include "Gate.h"
#include "TOF.h"
#include "IMU.h"
#include <HX711_ADC.h>
#include <Servo.h>
#include "LoadCell.h"
#include "collisionAvoidance.h"
#include "robotLocalisation.h"

/*******************************************************
 * Prototypes
 *******************************************************/
void attachInterrupts (void);
void detectOnBoardWeights (void);
void updateMotor1wrapper (void);
void updateMotor2wrapper (void);
void readEncoder1wrapper (void);
void readEncoder2wrapper (void);
void readJoystickwrapper (void);
void collectionDectection (void);
void rightEchoWrapper (void);
void leftEchoWrapper (void);
void checkEnemyBase (void);
void pollLoadCell (void);
void pollSensors (void);

/*******************************************************
 * Global variables
 *******************************************************/
bool TURN_RIGHT = false;
bool TURN_LEFT = false;
bool CAS_ACTIVE = false;
bool FULL = false;

unsigned long TIME_SINCE_COLLISION = 0;
int GLOBAL_ANGLE = 0;
int HOME_COLOUR = 0;
int NUM_WEIGHTS = 0;
int TURN_ANGLE = 0;
int DISTANCE = 0;
int X_POS = 0;
int Y_POS = 0;

/*******************************************************
 * Pins
 *******************************************************/
int rightSwitchPin = 30;
int leftSwitchPin = 31;
int rightServoPin = 32;
int leftServoPin = 33;
int rightTrigPin = 25;
int rightEchoPin = 24;
int leftTrigPin = 27;
int leftEchoPin = 26;
int encoderA[] = {2, 4};
int encoderB[] = {3, 5};
int motorPin[] = {7, 8};
int harvesterPin = 28; 
int loadCelldata = 0;
int loadCellclk = 1;
int goButtonPin = 23;
int vxPin = A5;
int vyPin = A4;
int swPin = 50;

/*******************************************************
 * Objects
 *******************************************************/
SX1509 io;
HX711_ADC cell(loadCelldata, loadCellclk);
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);Td
Ultrasonic rightSonar(rightTrigPin, rightEchoPin, 200, PRINT_SONARS);
Ultrasonic leftSonar(leftTrigPin, leftEchoPin, 200, PRINT_SONARS);
Motor leftMotor(motorPin[0], encoderA[0], encoderB[0], PRINT_MOTORS);
Motor rightMotor(motorPin[1], encoderA[1], encoderB[1], PRINT_MOTORS);
Joystick joystick(vxPin, vyPin, swPin, true);
Gate gate(leftServoPin, rightServoPin);
TOF rightTOF(0, &io, 'R', PRINT_TOFS);
TOF leftTOF(3, &io, 'L', PRINT_TOFS);
TOF frontTOF(2, &io, 'F', PRINT_TOFS);
TOF weightTOF(4, &io, 'W', PRINT_TOFS);
LoadCell loadCell(&cell, PRINT_LOAD);
Harvester harvester(harvesterPin);
IMU odom(&bno, PRINT_HEADING);
Colour colour(PRINT_COLOUR);
Scheduler runner;
Drive drive;

/*******************************************************
 * Tasks
 *******************************************************/ 
Task idleState(100, TASK_FOREVER, &idleUpdate, &runner, false, &idleInit, &idleCleanup);
Task manualState(100, TASK_FOREVER, &manualUpdate, &runner, false, &manualInit, &manualCleanup);
Task roamingState(100, TASK_FOREVER, &roamingUpdate, &runner, false, &roamingInit, &roamingCleanup);
Task pickUpState(50, TASK_FOREVER, &pickUpUpdate, &runner, false, &pickUpInit, &pickUpCleanup);
Task dropOffState(100, TASK_FOREVER, &dropOffUpdate, &runner, false, &dropOffInit, &dropOffCleanup);
Task collectionDetectionTask(50, TASK_FOREVER, &collectionDectection, &runner, false);
Task motor2task(MOTOR_PERIOD, TASK_FOREVER, &updateMotor2wrapper, &runner, true);
Task motor1task(MOTOR_PERIOD, TASK_FOREVER, &updateMotor1wrapper, &runner, true);
Task enemyBaseTask(100, TASK_FOREVER, &checkEnemyBase, &runner, false);
Task pollSensorsTask(100, TASK_FOREVER, &pollSensors, &runner, false);
Task CAStask(100, TASK_FOREVER, &updateCAS, &runner, false);
// Task localisationTask(100, TASK_FOREVER, &updatePath, &runner, false); // disabled forever
// Task loadCellTask(100, TASK_FOREVER, &pollLoadCell, &runner, false); // disabled forever

/*******************************************************
 * Core functions
 *******************************************************/
void setup() {  
  Serial.begin(9600);
  //frontTOF.initWire();
  attachInterrupts();
  pinMode(goButtonPin,INPUT); 
  initFSM(&idleState);
}
/*******************************************************/
void loop() { 
  runner.execute();
}

/*******************************************************
 * Attach interrupts for foreground tasks
 *******************************************************/
void attachInterrupts (void) {
  attachInterrupt(digitalPinToInterrupt(encoderA[0]), readEncoder1wrapper, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderA[1]), readEncoder2wrapper, RISING);
  attachInterrupt(digitalPinToInterrupt(leftEchoPin), leftEchoWrapper, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rightEchoPin), rightEchoWrapper, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(loadCelldata), loadCellWrapper, FALLING); // disabled forever
}

/*******************************************************
 * Wrapper functions
 *******************************************************/
void updateMotor1wrapper (void) {
  leftMotor.updateMotor();
}
/*******************************************************/
void updateMotor2wrapper (void) {
  rightMotor.updateMotor();
}
/*******************************************************/
void readEncoder1wrapper (void) {
  leftMotor.readEncoder();
}
/*******************************************************/
void readEncoder2wrapper (void) {
  rightMotor.readEncoder();
}
/*******************************************************/
void leftEchoWrapper (void) {
  leftSonar.echo();
}
/*******************************************************/
void rightEchoWrapper (void) {
  rightSonar.echo();
}
/*******************************************************/
void loadCellWrapper (void) {
  loadCell.dataReadyISR();
}
/*******************************************************/
void pollLoadCell (void) {
  loadCell.getWeight();
}
/*******************************************************/
void pollSensors (void) {
  leftTOF.updateRange();
  rightTOF.updateRange();
  frontTOF.updateRange();  

  if (leftSonar.isFinished()) {
    leftSonar.updateRange();
    leftSonar.pulse();
  }
  
  if (rightSonar.isFinished()) {
    rightSonar.updateRange();
    rightSonar.pulse();
  }
}
/*******************************************************/
void collectionDectection (void) {
  static unsigned long tc;
  weightTOF.updateRange(); 
  int TOFval = weightTOF.getRange();

  if (TOFval < 11 && TOFval != 0 && (millis()-tc)>1000) {
    tc = millis();
    NUM_WEIGHTS++;
  }

  if (NUM_WEIGHTS >= 3) {
    FULL = true;
    harvester.sweepAway();
  }

  if (PRINT_NUM_WEIGHTS) {
    Serial.print("Num weights: ");
    Serial.println(NUM_WEIGHTS);
  }
}
/*******************************************************/
void checkEnemyBase (void) {
  static bool atEnemyBase = false;
  if (!atEnemyBase && ((HOME_COLOUR == BLUE && colour.isGreen()) || (HOME_COLOUR == GREEN && colour.isBlue()))) {
    atEnemyBase = true;
    harvester.sweepAway();
  } 
  else if (atEnemyBase && ((HOME_COLOUR == BLUE && !colour.isGreen()) || (HOME_COLOUR == GREEN && !colour.isBlue()))) {
    atEnemyBase = false;
    harvester.sweepTowards();
  }  
}