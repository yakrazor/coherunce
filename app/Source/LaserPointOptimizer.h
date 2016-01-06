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
    void addLine(ildaPoint* points, int dwellOffPoints, int dwellOnPoints, int numSegments, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t r, uint16_t g, uint16_t b, uint16_t i);

    const LaserConfig& config;
    const LaserState& state;
};

#endif  // LASERPOINTOPTIMIZER_H_INCLUDED
