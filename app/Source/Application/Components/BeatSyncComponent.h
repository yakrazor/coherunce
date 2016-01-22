/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_83DDC134AF7E7A78__
#define __JUCE_HEADER_83DDC134AF7E7A78__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BeatSyncComponent  : public Component,
                           public ButtonListener,
                           public SliderListener
{
public:
    //==============================================================================
    BeatSyncComponent ();
    ~BeatSyncComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    class bpmListener : public Value::Listener {
    public:
        bpmListener(BeatSyncComponent* bsc) : Listener(), beatSyncComponent(bsc) {};
        void valueChanged(Value&);
    private:
        BeatSyncComponent* beatSyncComponent;
    };
    class clockSourceListener : public Value::Listener {
    public:
        clockSourceListener(BeatSyncComponent* bsc) : Listener(), beatSyncComponent(bsc) {};
        void valueChanged(Value&);
    private:
        BeatSyncComponent* beatSyncComponent;
    };
    class runningListener : public Value::Listener {
    public:
        runningListener(BeatSyncComponent* bsc) : Listener(), beatSyncComponent(bsc) {};
        void valueChanged(Value&);
    private:
        BeatSyncComponent* beatSyncComponent;
    };
    class quantListener : public Value::Listener {
    public:
        quantListener(BeatSyncComponent* bsc) : Listener(), beatSyncComponent(bsc) {};
        void valueChanged(Value&);
    private:
        BeatSyncComponent* beatSyncComponent;
    };
    ScopedPointer<bpmListener> bpmListen;
    ScopedPointer<clockSourceListener> clockSrcListen;
    ScopedPointer<runningListener> runningListen;
    ScopedPointer<quantListener> quantListen;

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<TextButton> tapTempoButton;
    ScopedPointer<TextButton> syncButton;
    ScopedPointer<Label> bpmLabel;
    ScopedPointer<TextButton> stopStartButton;
    ScopedPointer<TextButton> externalInternalToggle;
    ScopedPointer<Slider> bpmSlider;
    ScopedPointer<Label> beatClockLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BeatSyncComponent)
};

//[EndFile] You can add extra defines here...

//[/EndFile]

#endif   // __JUCE_HEADER_83DDC134AF7E7A78__
