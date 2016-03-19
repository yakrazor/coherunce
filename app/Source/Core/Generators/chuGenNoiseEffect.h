/*
  ==============================================================================

    chuGenNoiseEffect.h
    Created: 18 Mar 2016 6:04:12pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENNOISEEFFECT_H_INCLUDED
#define CHUGENNOISEEFFECT_H_INCLUDED

#include "chuGenerator.h"

class chuGenNoiseEffect : public chuGenerator {
public:
    chuGenNoiseEffect(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    chuParameterFloat* amount;
};



#endif  // CHUGENNOISEEFFECT_H_INCLUDED
