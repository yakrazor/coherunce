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

#ifndef __JUCE_HEADER_6EA8AC3BEE02F1B2__
#define __JUCE_HEADER_6EA8AC3BEE02F1B2__

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
class chuCalibrationComponent  : public Component,
                                 public SliderListener
{
public:
    //==============================================================================
    chuCalibrationComponent ();
    ~chuCalibrationComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    static void showCalibrationDialog();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> xBoundsSlider;
    ScopedPointer<Slider> yBoundsSlider;
    ScopedPointer<Slider> rotationSlider;
    ScopedPointer<GroupComponent> xBoundsGroup;
    ScopedPointer<GroupComponent> yBoundsGroup;
    ScopedPointer<GroupComponent> rotGroup;
    ScopedPointer<TextEditor> xMinBoundEditor;
    ScopedPointer<TextEditor> xMaxBoundEditor;
    ScopedPointer<TextEditor> yMinBoundEditor;
    ScopedPointer<TextEditor> yMaxBoundEditor;
    ScopedPointer<TextEditor> rotationBoundEditor;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuCalibrationComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_6EA8AC3BEE02F1B2__
