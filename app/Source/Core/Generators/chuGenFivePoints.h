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
    chuGenFivePoints(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    static constexpr float leapXMin = -300.0;
    static constexpr float leapXMax = 300.0;
    static constexpr float leapYMin = 60.0;
    static constexpr float leapYMax = 360.0;

    chuParameterInt* sides;
    chuParameterFloat* radius;
    chuParameterColor* color;
    chuParameterFloat* pt1x;
    chuParameterFloat* pt1y;
    chuParameterInt* pt1on;
    chuParameterFloat* pt2x;
    chuParameterFloat* pt2y;
    chuParameterInt* pt2on;
    chuParameterFloat* pt3x;
    chuParameterFloat* pt3y;
    chuParameterInt* pt3on;
    chuParameterFloat* pt4x;
    chuParameterFloat* pt4y;
    chuParameterInt* pt4on;
    chuParameterFloat* pt5x;
    chuParameterFloat* pt5y;
    chuParameterInt* pt5on;
};


#endif  // CHUGENFIVEPOINTS_H_INCLUDED
