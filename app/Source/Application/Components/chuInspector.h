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


class chuInspector : public Component
{
public:
    chuInspector();
    ~chuInspector();

    void paint(Graphics& g);
    void resized();

private:
    ScopedPointer<PropertyPanel> parameters;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuInspector)
};


#endif  // CHUINSPECTOR_H_INCLUDED
