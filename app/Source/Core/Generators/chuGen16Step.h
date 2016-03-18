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
    chuGen16Step(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    chuParameterFloat* height;
    chuParameterBool* quantized;
    chuParameterInt* numSteps;
    chuParameterFloat* pointiness;
    chuParameterColor* activeColor;
    chuParameterColor* restColor;
};


#endif  // CHUGEN16STEP_H_INCLUDED
