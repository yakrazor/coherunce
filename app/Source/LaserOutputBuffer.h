/*
  ==============================================================================

    LaserOutputBuffer.h
    Created: 5 Jan 2016 10:03:17pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASEROUTPUTBUFFER_H_INCLUDED
#define LASEROUTPUTBUFFER_H_INCLUDED

#include "chuThreadQueue.h"
#include "PatternItem.h"
#include "LaserPoint.h"

class LaserConfig;
class LaserState;

#define MAX_POINTS 3500

class LaserOutputBuffer
{
public:
    const ildaPoint* getPoints() { return points; }
    unsigned getPointCount() { return pointCount; }

    typedef chuThreadQueue<PatternItem> PatternQueue;
    PatternQueue& getPatternQueue() { return patternQueue; }

private:
    friend class LaserPointOptimizer;
    static const int maxPoints = MAX_POINTS;

    PatternQueue patternQueue;
    ildaPoint points[MAX_POINTS];
    unsigned int pointCount;
};

#endif  // LASEROUTPUTBUFFER_H_INCLUDED
