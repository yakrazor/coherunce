/*
  ==============================================================================

    chuGenJavascript.h
    Created: 16 Jan 2016 2:00:43am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENJAVASCRIPT_H_INCLUDED
#define CHUGENJAVASCRIPT_H_INCLUDED

#include "chuGenerator.h"


class chuGenJavascript : public chuGenerator {
public:
    chuGenJavascript();
    virtual std::vector<PatternItem> getPatterns(float barClock) override;
    virtual void getParamList(std::vector<chuParameter*>& params) override;

    ScopedPointer<chuParameterFloat> a;
    ScopedPointer<chuParameterFloat> b;
    ScopedPointer<chuParameterFloat> c;
    ScopedPointer<chuParameterFloat> d;
    
    ScopedPointer<chuParameterString> code;

    std::vector<PatternItem> patternBuffer;
    float localBarClock;
    Colour currentColour;
    
private:

    JavascriptEngine engine;
};



#endif  // CHUGENJAVASCRIPT_H_INCLUDED
