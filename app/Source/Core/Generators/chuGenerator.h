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
    chuGenerator(String generatorTypeName, ValueTree source = ValueTree("generator"));
    virtual ~chuGenerator() {}

    bool isActive() const;
    void setActive(bool b);

    virtual void setName(String generatorName) override;
    virtual const String getOSCRoot() const override;

    virtual std::vector<PatternItem> getPatterns(float barClock) = 0;

protected:

    chuParameterBool* active;
};



#endif  // CHUGENERATOR_H_INCLUDED
