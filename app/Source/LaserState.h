/*
  ==============================================================================

    LaserState.h
    Created: 6 Jan 2016 12:32:21am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASERSTATE_H_INCLUDED
#define LASERSTATE_H_INCLUDED

#include "LaserPoint.h"

class LaserState
{
public:
    LaserState();
    
    ildaPoint currentPoint;
    int redDelay;
    int greenDelay;
    int blueDelay;
};


#endif  // LASERSTATE_H_INCLUDED
