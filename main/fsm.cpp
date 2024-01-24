/*******************************************************
 *
 * fsm.cpp
 *
 * Implements finite state machine
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#include "global.h"

/*******************************************************
 * Local variables
 *******************************************************/
Task *currentTask;

/*******************************************************
 * Set initial task
 *******************************************************/
void initFSM (Task *initTask)
{
  currentTask = initTask;
  currentTask->enable();
}

/*******************************************************
 * Trigger state transition upon function call
 *******************************************************/
void changeState (Task *newTask)
{
  currentTask->disable();
  currentTask = newTask;
  currentTask->enable();
}

/*
void getState(Task *currentState, Event_t e)
{
  currentState->disable();

  switch ( currentState )
  {
  case IDLE_STATE:
    if ( e == goButtonPressed ) roamingState.enable();
    else if ( e == goButtonLongPressed ) manualState.enable();
    break;
  case MANUAL_STATE:
    if ( e == goButtonPressed ) idleState.enable();
    break;
  case ROAMING_STATE:
    if ( e == weightDetected ) pickUpState.enable();
    break;
  case PICK_UP_STATE:
    if ( e == weightCollected && atMaxCapcity) returnHomeState.enable();
    else if ( e == weighCollected ) roamingState.enable();
    break;
  case RETURN_HOME_STATE:
    if ( e == atHome ) dropOffState.enable();
    break;
  case DROP_OFF_STATE:
    if ( e == weightsDeposited ) roamingState.enable();
    break;
  default:
    idleState.enable();
  }
}*/
