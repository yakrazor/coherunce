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

class chuGeneratorManager
{
public:
    chuGeneratorManager();
    
    static OwnedArray<chuGenerator>& getAllGenerators() { return allGenerators; }
private:
    static OwnedArray<chuGenerator> allGenerators;
};



#endif  // CHUGENERATORMANAGER_H_INCLUDED
