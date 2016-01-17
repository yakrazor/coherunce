/*
  ==============================================================================

    LaserPoint.h
    Created: 6 Jan 2016 12:38:55am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASERPOINT_H_INCLUDED
#define LASERPOINT_H_INCLUDED

#include <stdint.h>

struct ildaPoint {

    ildaPoint() : x(0), y(0), r(0), g(0), b(0), i(0), u1(0), u2(0) {}

    int16_t x;
    int16_t y;
    uint16_t r;
    uint16_t g;
    uint16_t b;
    uint16_t i;
    uint16_t u1;
    uint16_t u2;

    static const ildaPoint zero;
};


#endif  // LASERPOINT_H_INCLUDED
