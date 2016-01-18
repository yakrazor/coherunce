/*
  ==============================================================================

    chuPreferencesPageOSC.cpp
    Created: 25 Dec 2015 7:56:45pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuApplication.h"
#include "chuPreferencesDialog.h"

class chuPreferencePageOSCContent : public Component
{
public:
    chuPreferencePageOSCContent()
    {
        incomingPort = new TextEditor();
        incomingPort->insertTextAtCaret("7900");
        addAndMakeVisible(incomingPort);
        incomingPortLabel = new Label(String::empty, "Incoming port:");
        incomingPortLabel->setJustificationType(Justification::centredRight);
        addAndMakeVisible(incomingPortLabel);
    }

    ~chuPreferencePageOSCContent()
    {
    }

    void resized() override
    {
        Rectangle<int> r (proportionOfWidth (0.35f), 0, proportionOfWidth (0.6f), 3000);
        int h = 26;
        int space = h / 4;

        r.removeFromTop(space * 2);

        if (incomingPort != nullptr)
        {
            auto row = r.removeFromTop(h);
            incomingPort->setBounds(row);
            incomingPortLabel->setBounds(0, incomingPort->getBounds().getCentreY() - h / 2, r.getX(), h);
        }
    }

private:

    ScopedPointer<TextEditor> incomingPort;
    ScopedPointer<Label> incomingPortLabel;
};

class chuPreferencesPageOSC : public Component
{
public:
    chuPreferencesPageOSC()
    {
        pageContent = new chuPreferencePageOSCContent();
        addAndMakeVisible(pageContent);

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
    }

    ~chuPreferencesPageOSC()
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
        pageContent->setBounds(r.removeFromTop(proportionOfHeight(0.65f)));
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
    ScopedPointer<chuPreferencePageOSCContent> pageContent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuPreferencesPageOSC)
};

static chuPreferencePageProvider<chuPreferencesPageOSC> page("OSC");
