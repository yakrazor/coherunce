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

class chuClipButton : public Component, Button::Listener, Timer
{
public:
    chuClipButton();
    ~chuClipButton();

    virtual void paint(Graphics& g) override;
    virtual void resized() override;
    virtual void timerCallback() override;

    void setGenerator(chuGenerator* gen);
    chuGenerator* getGenerator() { return generator; }

    void setFocus(bool focused);
    void updatePreview();

    virtual void buttonClicked(Button* button) override;

private:
    chuGenerator* generator;

    int labelHeight;
    int borderWidth;

    ScopedPointer<DrawableComposite> preview;
    ScopedPointer<DrawableButton> mainButton;
    ScopedPointer<TextButton> labelButton;
    
    const int previewHz = 60;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuClipButton)
};


#endif  // CHUCLIPBUTTON_H_INCLUDED
