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

    virtual void paint(Graphics& g) override;
    virtual void resized() override;

    void inspectParameters(chuParameterProvider* provider);

    virtual void changeListenerCallback(ChangeBroadcaster* source) override;

private:
    ChangeBroadcaster* broadcaster;
    ScopedPointer<PropertyPanel> panel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuInspector)
};


#endif  // CHUINSPECTOR_H_INCLUDED
