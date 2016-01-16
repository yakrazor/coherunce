/*
  ==============================================================================

    chuGenPolygonPinwheel.h
    Created: 16 Jan 2016 1:51:26am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENPOLYGONPINWHEEL_H_INCLUDED
#define CHUGENPOLYGONPINWHEEL_H_INCLUDED

#include "chuGenerator.h"


class chuGenPolygonPinwheel : public chuGenerator {
public:
    chuGenPolygonPinwheel();
    virtual std::vector<PatternItem> getPatterns(float barClock) override;
    virtual void getParamList(std::vector<chuParameter*>& params) override;
    ScopedPointer<chuParameterInt> sides;
    ScopedPointer<chuParameterFloat> radius;
    ScopedPointer<chuParameterInt> copies;
    ScopedPointer<chuParameterFloat> scale;
    ScopedPointer<chuParameterColor> color;
};


#endif  // CHUGENPOLYGONPINWHEEL_H_INCLUDED
