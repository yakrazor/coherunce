/*
  ==============================================================================

    chuGen16Step.h
    Created: 16 Jan 2016 1:52:05am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGEN16STEP_H_INCLUDED
#define CHUGEN16STEP_H_INCLUDED

#include "chuGenerator.h"


class chuGen16Step : public chuGenerator {
public:
    chuGen16Step();
    virtual std::vector<PatternItem> getPatterns(float barClock) override;
    virtual void getParamList(std::vector<chuParameter*>& params) override;

    ScopedPointer<chuParameterFloat> height;
    ScopedPointer<chuParameterBool> quantized;
    ScopedPointer<chuParameterInt> numSteps;
    ScopedPointer<chuParameterFloat> pointiness;
    ScopedPointer<chuParameterColor> activeColor;
    ScopedPointer<chuParameterColor> restColor;
};


#endif  // CHUGEN16STEP_H_INCLUDED
