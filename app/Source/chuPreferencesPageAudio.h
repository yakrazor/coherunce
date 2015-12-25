/*
  ==============================================================================

    AudioSettingsPage.h
    Created: 24 Dec 2015 10:54:29pm
    Author:  Michael Dewberry
 
    copied largely from JuceDemo

  ==============================================================================
*/

#ifndef AUDIOSETTINGSPAGE_H_INCLUDED
#define AUDIOSETTINGSPAGE_H_INCLUDED

#include "chuApplication.h"

class chuPreferencesPageAudio : public Component, public ChangeListener
{
public:
    chuPreferencesPageAudio()
    {
        setOpaque(true);

        addAndMakeVisible(
                          audioSetupComp
                          = new AudioDeviceSelectorComponent(getApp()->getSharedAudioDeviceManager(),
                                                             0, 256, 0, 256, true, true, true, false)
                          );

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

        getApp()->getSharedAudioDeviceManager().addChangeListener(this);

        logMessage ("Audio device diagnostics:\n");
        dumpDeviceInfo();
    }

    ~chuPreferencesPageAudio()
    {
        getApp()->getSharedAudioDeviceManager().removeChangeListener(this);
        diagnosticsBox.clear();
    }

    void paint (Graphics& g) override
    {
        g.fillAll(Colours::grey);   // clear the background

    }

    void resized() override
    {
        Rectangle<int> r(getLocalBounds().reduced(4));
        audioSetupComp->setBounds(r.removeFromTop(proportionOfHeight(0.65f)));
        diagnosticsBox.setBounds(r);
    }

    void dumpDeviceInfo()
    {
        AudioDeviceManager& dm = getApp()->getSharedAudioDeviceManager();

        logMessage("--------------------------------------");
        logMessage("Current audio device type: " + (dm.getCurrentDeviceTypeObject() != nullptr
                                                        ? dm.getCurrentDeviceTypeObject()->getTypeName()
                                                        : "<none>"));

        if (AudioIODevice* device = dm.getCurrentAudioDevice())
        {
            logMessage("Current audio device: " + device->getName().quoted());
            logMessage("Sample rate: " + String (device->getCurrentSampleRate()) + " Hz");
            logMessage("Block size: " + String (device->getCurrentBufferSizeSamples()) + " samples");
            logMessage("Output Latency: " + String (device->getOutputLatencyInSamples()) + " samples");
            logMessage("Input Latency: " + String (device->getInputLatencyInSamples()) + " samples");
            logMessage("Bit depth: " + String (device->getCurrentBitDepth()));
            logMessage("Input channel names: " + device->getInputChannelNames().joinIntoString (", "));
            logMessage("Active input channels: " + getListOfActiveBits (device->getActiveInputChannels()));
            logMessage("Output channel names: " + device->getOutputChannelNames().joinIntoString (", "));
            logMessage("Active output channels: " + getListOfActiveBits (device->getActiveOutputChannels()));
        }
        else
        {
            logMessage("No audio device open");
        }
    }

    void logMessage(const String& m)
    {
        diagnosticsBox.moveCaretToEnd();
        diagnosticsBox.insertTextAtCaret(m + newLine);
    }

private:
    ScopedPointer<AudioDeviceSelectorComponent> audioSetupComp;
    TextEditor diagnosticsBox;

    void changeListenerCallback(ChangeBroadcaster*) override
    {
        dumpDeviceInfo();
    }

    static String getListOfActiveBits(const BitArray& b)
    {
        StringArray bits;

        for (int i = 0; i <= b.getHighestBit(); ++i)
            if (b[i])
                bits.add(String (i));

        return bits.joinIntoString(", ");
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuPreferencesPageAudio)
};


#endif  // AUDIOSETTINGSPAGE_H_INCLUDED
