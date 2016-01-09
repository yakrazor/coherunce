/*
  ==============================================================================

    chuClipButton.h
    Created: 8 Jan 2016 7:25:48pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUCLIPBUTTON_H_INCLUDED
#define CHUCLIPBUTTON_H_INCLUDED

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/

class chuGenerator;

class chuClipButton : public Component, Button::Listener
{
public:
    chuClipButton();
    ~chuClipButton();

    virtual void paint(Graphics& g) override;
    virtual void resized() override;

    void setGenerator(chuGenerator* gen);

    virtual void buttonClicked(Button* button) override;

private:
    chuGenerator* generator;

    int labelHeight;

    ScopedPointer<DrawableComposite> preview;
    ScopedPointer<DrawableButton> mainButton;
    ScopedPointer<TextButton> labelButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuClipButton)
};


#endif  // CHUCLIPBUTTON_H_INCLUDED
