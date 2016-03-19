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
    chuGenJavascript(ValueTree source = ValueTree("generator"));
    virtual void getPatterns(float barClock, std::vector<PatternItem>& patterns) override;

    chuParameterFloat* a;
    chuParameterFloat* b;
    chuParameterFloat* c;
    chuParameterFloat* d;
    
    chuParameterString* code;

    std::vector<PatternItem> patternBuffer;
    float localBarClock;
    int localBarCount;
    Colour currentColour;
    
private:

    JavascriptEngine engine;
};



#endif  // CHUGENJAVASCRIPT_H_INCLUDED
