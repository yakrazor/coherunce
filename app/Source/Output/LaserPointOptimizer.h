/*
  ==============================================================================

    LaserPointOptimizer.h
    Created: 6 Jan 2016 12:27:36am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASERPOINTOPTIMIZER_H_INCLUDED
#define LASERPOINTOPTIMIZER_H_INCLUDED

#include "LaserPoint.h"
#include "PatternItem.h"

class LaserOutputBuffer;
class LaserConfig;
class LaserState;

class LaserPointOptimizer
{
public:
    LaserPointOptimizer(const LaserConfig& _config, const LaserState& _state);
    void fillBufferFromFrame(LaserOutputBuffer& buffer);
private:

    unsigned pointIndex;
    bool addLine(ildaPoint* points, float fx1, float fy1, float fx2, float fy2, const Colour& startColour, const Colour& endColour, uint16_t i);

    const LaserConfig& config;
    const LaserState& state;
};

#endif  // LASERPOINTOPTIMIZER_H_INCLUDED
