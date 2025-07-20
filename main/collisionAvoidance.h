/*******************************************************
 *
 * collisionAvoidance.h
 *
 * Support collisionAvoidance.cpp module
 *
 * Authors: T.J. Mitchell
 * Last modified: 17/10/22
 *
 *******************************************************/

#define BOTTOM_TOF_THRESH 0
#define FRONT_TOF_THRESH 25
#define SONAR_THRESH 25

 /*******************************************************
 * Prototypes
 *******************************************************/
void updateCAS (void);
bool checkWallLeft (void);
bool checkWallRight (void);
bool checkWallAhead (void);
