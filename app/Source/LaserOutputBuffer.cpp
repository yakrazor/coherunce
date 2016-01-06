/*
  ==============================================================================

    LaserOutputBuffer.cpp
    Created: 5 Jan 2016 10:03:17pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "LaserOutputBuffer.h"

ildaPoint* LaserOutputBuffer::getPoints()
{
    return points;
}

struct ildaPoint points[NUM_POINTS];