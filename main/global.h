#ifndef GLOBAL_H_
#define GLOBAL_H_

/*******************************************************
 *
 * global.h
 * 
 * Header file for global variables and objects
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include <Servo.h>
#include "Motor.h"
#include "Joystick.h"
#include <HX711_ADC.h>
#include "Ultrasonic.h"
#include "Harvester.h"
#include "LoadCell.h"
#include "Colour.h"
#include "Drive.h"
#include "Gate.h"
#include "TOF.h"
#include "IMU.h"
#include <SparkFunSX1509.h>
#include <Adafruit_BNO055.h>
#define _TASK_SLEEP_ON_IDLE_RUN
#include <TaskSchedulerDeclarations.h>

/*******************************************************
 * Macros
 *******************************************************/
#define UPDATE_RATE     50
#define CRUISING_RPM    60
#define SENSOR_ANGLE    35
#define HALF_WIDTH      12
#define ERROR_TOL       10
#define BLUE            0
#define GREEN           1

#define PRINT_LOAD        false
#define PRINT_STATES      false
#define PRINT_TOFS        true
#define PRINT_SONARS      false
#define PRINT_MOTORS      false
#define PRINT_FLAGS       false
#define PRINT_HEADING     false
#define PRINT_NUM_WEIGHTS true
#define PRINT_COLOUR      false
 
 /*******************************************************
 * Global variables
 *******************************************************/
extern bool CAS_ACTIVE;
extern bool TURN_LEFT;
extern bool TURN_RIGHT;
extern bool FULL;

extern unsigned long TIME_SINCE_COLLISION;
extern int GLOBAL_ANGLE;
extern int HOME_COLOUR;
extern int NUM_WEIGHTS;
extern int TURN_ANGLE;
extern int DISTANCE;
extern int X_POS;
extern int Y_POS;

/*******************************************************
 * Pins
 *******************************************************/
extern int rightSwitchPin;
extern int leftSwitchPin;
extern int rightServoPin;
extern int leftServoPin;
extern int rightTrigPin;
extern int rightEchoPin;
extern int leftTrigPin;
extern int leftEchoPin;
extern int encoderA[];
extern int encoderB[];
extern int motorPin[];
extern int harvesterPin;
extern int loadCelldata;
extern int loadCellclk;
extern int goButtonPin;
extern int vxPin;
extern int vyPin;
extern int swPin;

/*******************************************************
 * Global objects
 *******************************************************/
extern SX1509 io;
extern HX711_ADC cell;
extern Adafruit_BNO055 bno;
extern Ultrasonic rightSonar;
extern Ultrasonic leftSonar;
extern Harvester harvester;
extern Joystick joystick;
extern LoadCell loadCell;
extern Scheduler runner;
extern Motor rightMotor;
extern Motor leftMotor;
extern Colour colour;
extern TOF frontTOF;
extern TOF rightTOF;
extern TOF leftTOF;
extern TOF weightTOF;
extern Drive drive;
extern Gate gate;
extern IMU odom;

/*******************************************************
 * Tasks
 *******************************************************/ 
extern Task idleState;
extern Task manualState;
extern Task roamingState;
extern Task pickUpState;
extern Task dropOffState;
extern Task pollSensorsTask;
extern Task CAStask;
extern Task localisationTask;
extern Task enemyBaseTask;
extern Task collectionDetectionTask;

#endif
