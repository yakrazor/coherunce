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


chuInspector::chuInspector(ChangeBroadcaster* bc)
{
    broadcaster = bc;
    if (broadcaster)
    {
        broadcaster->addChangeListener(this);
    }
}

void chuInspector::inspectParameters(chuParameterProvider* provider)
{
    if (panel)
    {
        removeChildComponent(panel);
    }

    if (provider)
    {
        panel = provider->createPanel();
        addAndMakeVisible(panel);
        panel->setBounds(getLocalBounds());
    }
}

chuInspector::~chuInspector()
{
    if (broadcaster)
    {
        broadcaster->removeChangeListener(this);
    }
}

void chuInspector::paint(Graphics& g)
{
    g.fillAll(Colours::black);
}

void chuInspector::resized()
{
    if (panel)
    {
        panel->setBounds(getLocalBounds());
    }
}

void chuInspector::changeListenerCallback(ChangeBroadcaster* source)
{
    chuGeneratorManager* mgr = dynamic_cast<chuGeneratorManager*>(source);
    if (mgr)
    {
        inspectParameters(mgr->getCurrentGenerator());
    }
}
