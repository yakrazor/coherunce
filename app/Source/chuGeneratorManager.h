/*
  ==============================================================================

    chuGeneratorManager.h
    Created: 30 Dec 2015 3:02:20pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGENERATORMANAGER_H_INCLUDED
#define CHUGENERATORMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "chuGenerator.h"

class chuGeneratorManager : public ChangeBroadcaster
{
public:
    chuGeneratorManager();
    ~chuGeneratorManager();

    OwnedArray<chuGenerator>& getAllGenerators() { return allGenerators; }

    chuGenerator* getCurrentGenerator() { return currentGenerator; }
    void setCurrentGenerator(chuGenerator* gen);

private:
    OwnedArray<chuGenerator> allGenerators;
    chuGenerator* currentGenerator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuGeneratorManager)
};

chuGeneratorManager* getGeneratorManager();
void clearGeneratorManager();


#endif  // CHUGENERATORMANAGER_H_INCLUDED
