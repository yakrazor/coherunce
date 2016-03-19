/*
  ==============================================================================

    chuGenHandplane.h
    Created: 18 Mar 2016 9:33:03pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENHANDPLANE_H_INCLUDED
#define CHUGENHANDPLANE_H_INCLUDED

#include "chuGenerator.h"


class chuGenHandplane : public chuGenerator {
public:
    chuGenHandplane(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    static constexpr float leapXMin = -300.0;
    static constexpr float leapXMax = 300.0;
    static constexpr float leapYMin = 60.0;
    static constexpr float leapYMax = 360.0;

    chuParameterColor* color1;
    chuParameterColor* color2;
    chuParameterBool* extend;

    chuParameterFloat* pt2x;
    chuParameterFloat* pt2y;
    chuParameterFloat* pt3x;
    chuParameterFloat* pt3y;
};




#endif  // CHUGENHANDPLANE_H_INCLUDED
