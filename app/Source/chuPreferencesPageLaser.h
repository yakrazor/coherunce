/*
  ==============================================================================

    chuPreferencesPageLaser.h
    Created: 25 Dec 2015 7:56:45pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUPREFERENCESPAGELASER_H_INCLUDED
#define CHUPREFERENCESPAGELASER_H_INCLUDED

#include "chuApplication.h"

class chuPreferencesPageLaser : public Component
{
public:
    chuPreferencesPageLaser()
    {
        addAndMakeVisible(diagnosticsBox);
        diagnosticsBox.setMultiLine(true);
        diagnosticsBox.setReturnKeyStartsNewLine(true);
        diagnosticsBox.setReadOnly(true);
        diagnosticsBox.setScrollbarsShown(true);
        diagnosticsBox.setCaretVisible(false);
        diagnosticsBox.setPopupMenuEnabled(true);
        diagnosticsBox.setColour(TextEditor::textColourId, Colours::white);
        diagnosticsBox.setColour(TextEditor::backgroundColourId, Colour (0x32ffffff));
        diagnosticsBox.setColour(TextEditor::outlineColourId, Colour (0x1c000000));
        diagnosticsBox.setColour(TextEditor::shadowColourId, Colour (0x16000000));

        logMessage ("Laser device diagnostics:\n");
        dumpDeviceInfo();
    }

    ~chuPreferencesPageLaser()
    {
        diagnosticsBox.clear();
    }

    void paint (Graphics& g)
    {
        g.fillAll(Colours::skyblue);
    }

    void resized()
    {
        Rectangle<int> r(getLocalBounds().reduced(4));
        diagnosticsBox.setBounds(r);
    }

    void dumpDeviceInfo()
    {
        // TODO: implement me
        logMessage("\nTODO: implement me\n");

        /*
        if (connected)
        {

        }
        else
        {
            logMessage("No laser DACs found");
        }
        */
    }

    void logMessage(const String& m)
    {
        diagnosticsBox.moveCaretToEnd();
        diagnosticsBox.insertTextAtCaret(m + newLine);
    }

private:
    TextEditor diagnosticsBox;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuPreferencesPageLaser)
};


#endif  // CHUPREFERENCESPAGELASER_H_INCLUDED
