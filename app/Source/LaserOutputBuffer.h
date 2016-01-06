/*
  ==============================================================================

    LaserOutputBuffer.h
    Created: 5 Jan 2016 10:03:17pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASEROUTPUTBUFFER_H_INCLUDED
#define LASEROUTPUTBUFFER_H_INCLUDED

#include <stdint.h>
#include "chuThreadQueue.h"
#include "PatternItem.h"

struct ildaPoint {
    int16_t x;
    int16_t y;
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t i;
    uint16_t u1;
    uint16_t u2;
};

#define NUM_POINTS 3500


class LaserOutputBuffer
{
public:
    ildaPoint* getPoints();
    unsigned getPointCount() { return pointCount; }
    // TODO: remove this
    void setPointCount(unsigned count) { pointCount = count; }

    typedef chuThreadQueue<PatternItem> PatternQueue;
    PatternQueue& getPatternQueue() { return patternQueue; }

private:
    PatternQueue patternQueue;
    struct ildaPoint points[NUM_POINTS];
    unsigned int pointCount;
};

#endif  // LASEROUTPUTBUFFER_H_INCLUDED
