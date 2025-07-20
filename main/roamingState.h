#ifndef ROAMINGSTATE_H_
#define ROAMINGSTATE_H_

/*******************************************************
 *
 * roamingState.h
 *
 * Supports roamingState.cpp module
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

/*******************************************************
 * Prototypes
 *******************************************************/
bool roamingInit (void);
void roamingCleanup (void);
void roamingUpdate (void);
bool weightLeft (void);
bool weightRight (void);

#endif 
