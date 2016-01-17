/*
  ==============================================================================

    chuInspector.h
    Created: 15 Jan 2016 12:09:25am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUINSPECTOR_H_INCLUDED
#define CHUINSPECTOR_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "chuParameters.h"


class chuInspector : public Component, public ChangeListener
{
public:
    chuInspector(ChangeBroadcaster* broadcaster);
    ~chuInspector();

    void paint(Graphics& g);
    void resized();

    void inspectParameters(chuParameterProvider* provider);

    virtual void changeListenerCallback(ChangeBroadcaster* source) override;

private:
    ScopedPointer<PropertyPanel> panel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuInspector)
};


#endif  // CHUINSPECTOR_H_INCLUDED
