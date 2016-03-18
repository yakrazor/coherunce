/*
  ==============================================================================

    chuGenTranslateEffect.h
    Created: 18 Mar 2016 10:43:04am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENTRANSLATEEFFECT_H_INCLUDED
#define CHUGENTRANSLATEEFFECT_H_INCLUDED

#include "chuGenerator.h"

class chuGenTranslateEffect : public chuGenerator {
public:
    chuGenTranslateEffect(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    chuParameterFloat* manualShiftX;
    chuParameterFloat* manualShiftY;
    chuParameterInt* beatCount1X;
    chuParameterFloat* beatShift1X;
    chuParameterInt* beatCount2X;
    chuParameterFloat* beatShift2X;
    chuParameterInt* beatCount1Y;
    chuParameterFloat* beatShift1Y;
    chuParameterInt* beatCount2Y;
    chuParameterFloat* beatShift2Y;
};



#endif  // CHUGENTRANSLATEEFFECT_H_INCLUDED
