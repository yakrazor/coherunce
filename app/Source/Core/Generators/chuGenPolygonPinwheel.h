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
    chuGenPolygonPinwheel(ValueTree source = ValueTree("generator"));
    virtual std::vector<PatternItem> getPatterns(float barClock, std::vector<PatternItem>& existingPatterns) override;

    chuParameterInt* sides;
    chuParameterFloat* radius;
    chuParameterInt* copies;
    chuParameterFloat* scale;
    chuParameterColor* color;
};


#endif  // CHUGENPOLYGONPINWHEEL_H_INCLUDED
