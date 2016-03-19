/*
  ==============================================================================

    chuGenSinusoidEffect.h
    Created: 18 Mar 2016 6:03:54pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENSINUSOIDEFFECT_H_INCLUDED
#define CHUGENSINUSOIDEFFECT_H_INCLUDED


#include "chuGenerator.h"

class chuGenSinusoidEffect : public chuGenerator {
public:
    chuGenSinusoidEffect(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    chuParameterFloat* amount;
    chuParameterInt* samples;
};

#endif  // CHUGENSINUSOIDEFFECT_H_INCLUDED
