/*
  ==============================================================================

    chuGlobalControls.h
    Created: 15 Jan 2016 12:06:38am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUGLOBALCONTROLS_H_INCLUDED
#define CHUGLOBALCONTROLS_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"


class chuGlobalControls : public Component, public Button::Listener, public Slider::Listener
{
public:
    chuGlobalControls();
    ~chuGlobalControls();

    void paint(Graphics& g);
    void resized();

    virtual void buttonClicked(Button* button) override;
    virtual void sliderValueChanged (Slider* slider) override;

private:
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<Slider> intensitySlider;
    ScopedPointer<Label> intensityLabel;
    ScopedPointer<TextButton> enableButton;

    ScopedPointer<Component> beatSyncComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(chuGlobalControls)
};


#endif  // CHUGLOBALCONTROLS_H_INCLUDED
