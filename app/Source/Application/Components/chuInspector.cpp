/*
  ==============================================================================

    chuInspector.cpp
    Created: 15 Jan 2016 12:09:25am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuInspector.h"
#include "chuGeneratorManager.h"


chuInspector::chuInspector()
{
    parameters = chuGeneratorManager::getAllGenerators()[0]->createPanel();
    addAndMakeVisible(parameters);
}

chuInspector::~chuInspector()
{
}

void chuInspector::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void chuInspector::resized()
{
    parameters->setBounds(getLocalBounds());
}
