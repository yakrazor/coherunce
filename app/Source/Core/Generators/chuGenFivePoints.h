/*
  ==============================================================================

    chuGenFivePoints.h
    Created: 16 Jan 2016 1:52:58am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENFIVEPOINTS_H_INCLUDED
#define CHUGENFIVEPOINTS_H_INCLUDED

#include "chuGenerator.h"


class chuGenFivePoints : public chuGenerator {
public:
    chuGenFivePoints();
    virtual std::vector<PatternItem> getPatterns(float barClock) override;
    virtual void getParamList(std::vector<chuParameter*>& params) override;

    static constexpr float leapXMin = -300.0;
    static constexpr float leapXMax = 300.0;
    static constexpr float leapYMin = 60.0;
    static constexpr float leapYMax = 360.0;

    ScopedPointer<chuParameterInt> sides;
    ScopedPointer<chuParameterFloat> radius;
    ScopedPointer<chuParameterColor> color;

    ScopedPointer<chuParameterFloat> pt1x;
    ScopedPointer<chuParameterFloat> pt1y;
    ScopedPointer<chuParameterInt> pt1on;
    ScopedPointer<chuParameterFloat> pt2x;
    ScopedPointer<chuParameterFloat> pt2y;
    ScopedPointer<chuParameterInt> pt2on;
    ScopedPointer<chuParameterFloat> pt3x;
    ScopedPointer<chuParameterFloat> pt3y;
    ScopedPointer<chuParameterInt> pt3on;
    ScopedPointer<chuParameterFloat> pt4x;
    ScopedPointer<chuParameterFloat> pt4y;
    ScopedPointer<chuParameterInt> pt4on;
    ScopedPointer<chuParameterFloat> pt5x;
    ScopedPointer<chuParameterFloat> pt5y;
    ScopedPointer<chuParameterInt> pt5on;
};


#endif  // CHUGENFIVEPOINTS_H_INCLUDED
