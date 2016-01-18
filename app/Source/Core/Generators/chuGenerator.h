/*
  ==============================================================================

    chuGenerator.h
    Created: 30 Dec 2015 1:32:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENERATOR_H_INCLUDED
#define CHUGENERATOR_H_INCLUDED

#include <vector>
#include "../JuceLibraryCode/JuceHeader.h"
#include "PatternItem.h"
#include "chuParameters.h"


class chuGenerator : public chuParameterProvider {
public:
    chuGenerator(String generatorName);
    virtual ~chuGenerator() {}

    virtual String getName() const override { return name; }
    bool isActive() const { return active; }
    void setActive(bool b) { active = b; }

    void setOSCAddress(const String& addr);

    virtual void init() {};
    virtual std::vector<PatternItem> getPatterns(float barClock) = 0;
    virtual void getParamList(std::vector<chuParameter*>& params) override {};

private:
    String name;
    bool active;
};



#endif  // CHUGENERATOR_H_INCLUDED
