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

    bool isActive() const;
    void setActive(bool b);

    void setOSCAddress(const String& addr);

    virtual std::vector<PatternItem> getPatterns(float barClock) = 0;

protected:
    chuParameterBool* active;
};



#endif  // CHUGENERATOR_H_INCLUDED
