/*
  ==============================================================================

    chuLookAndFeel.h
    Created: 8 Jan 2016 10:03:38pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHULOOKANDFEEL_H_INCLUDED
#define CHULOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class chuLookAndFeel : public LookAndFeel_V3
{
public:
    chuLookAndFeel();

    virtual void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                       bool isMouseOverButton, bool isButtonDown) override;
};



#endif  // CHULOOKANDFEEL_H_INCLUDED
