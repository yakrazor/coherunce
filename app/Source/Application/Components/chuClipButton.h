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
#include "chuGeneratorPreview.h"
//==============================================================================
/*
*/


class chuGenerator;

class chuClipButton : public Component, Button::Listener, ChangeListener
{
public:
    chuClipButton();

    virtual void paint(Graphics& g) override;
    virtual void resized() override;

    void setGenerator(chuGenerator* gen);
    chuGenerator* getGenerator() { return generator; }

    void setFocus(bool focused);

    virtual void buttonClicked(Button* button) override;
    virtual void changeListenerCallback(ChangeBroadcaster *source) override;

private:
    chuGenerator* generator;

    int labelHeight;
    int borderWidth;

    ScopedPointer<chuGeneratorPreview> preview;
    ScopedPointer<DrawableButton> mainButton;
    ScopedPointer<TextButton> labelButton;
    
    const int previewHz = 30;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuClipButton)
};


#endif  // CHUCLIPBUTTON_H_INCLUDED
