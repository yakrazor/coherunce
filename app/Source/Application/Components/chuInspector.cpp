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
: panel(new PropertyPanel())
{
    addAndMakeVisible(panel);

    broadcaster = bc;
    if (broadcaster)
    {
        broadcaster->addChangeListener(this);
    }
}

void chuInspector::inspectParameters(chuParameterProvider* provider)
{
    panel->setBounds(getLocalBounds());
    panel->clear();

    if (provider)
    {
        provider->createPanel(panel);
    }

    for (auto globalEffect : getGeneratorManager()->getGlobalEffects())
    {
        globalEffect->createPanel(panel);
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
