#ifndef FSM_H_
#define FSM_H_

/*******************************************************
 *
 * fsm.h
 *
 * Supports fsm.cpp module
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

/*******************************************************
 * Prototypes
 *******************************************************/
void initFSM (Task *initTask); // Set initial task
void changeState (Task *newTask); // Trigger state transition upon function call

#endif 
