/*
  ==============================================================================

    chuGenRecolorEffect.h
    Created: 17 Mar 2016 9:20:13pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENRECOLOREFFECT_H_INCLUDED
#define CHUGENRECOLOREFFECT_H_INCLUDED

#include "chuGenerator.h"

class chuGenRecolorEffect : public chuGenerator {
public:
    chuGenRecolorEffect(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    chuParameterColor* color1;
    chuParameterColor* color2;
};

#endif  // CHUGENRECOLOREFFECT_H_INCLUDED
