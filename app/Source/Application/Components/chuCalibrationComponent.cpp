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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "chuCalibrationComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
chuCalibrationComponent::chuCalibrationComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (xBoundsSlider = new Slider ("x bounds slider"));
    xBoundsSlider->setRange (0, 100, 0);
    xBoundsSlider->setSliderStyle (Slider::TwoValueHorizontal);
    xBoundsSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    xBoundsSlider->setColour (Slider::backgroundColourId, Colour (0x00000000));
    xBoundsSlider->addListener (this);

    addAndMakeVisible (yBoundsSlider = new Slider ("y bounds slider"));
    yBoundsSlider->setRange (0, 10, 0);
    yBoundsSlider->setSliderStyle (Slider::TwoValueVertical);
    yBoundsSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    yBoundsSlider->addListener (this);

    addAndMakeVisible (rotationSlider = new Slider ("rotation slider"));
    rotationSlider->setRange (0, 10, 0);
    rotationSlider->setSliderStyle (Slider::Rotary);
    rotationSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    rotationSlider->setColour (Slider::trackColourId, Colours::white);
    rotationSlider->setColour (Slider::rotarySliderFillColourId, Colour (0xfffffefe));
    rotationSlider->setColour (Slider::rotarySliderOutlineColourId, Colours::white);
    rotationSlider->addListener (this);

    addAndMakeVisible (xBoundsGroup = new GroupComponent ("x bounds group",
                                                          TRANS("X bounds")));
    xBoundsGroup->setTextLabelPosition (Justification::centredLeft);
    xBoundsGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    xBoundsGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (yBoundsGroup = new GroupComponent ("y bounds group",
                                                          TRANS("Y bounds")));
    yBoundsGroup->setTextLabelPosition (Justification::centredLeft);
    yBoundsGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    yBoundsGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (rotGroup = new GroupComponent ("rotation group",
                                                      TRANS("Rotation")));
    rotGroup->setTextLabelPosition (Justification::centredLeft);
    rotGroup->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    rotGroup->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (xMinBoundEditor = new TextEditor ("x min bound editor"));
    xMinBoundEditor->setMultiLine (false);
    xMinBoundEditor->setReturnKeyStartsNewLine (false);
    xMinBoundEditor->setReadOnly (false);
    xMinBoundEditor->setScrollbarsShown (true);
    xMinBoundEditor->setCaretVisible (true);
    xMinBoundEditor->setPopupMenuEnabled (true);
    xMinBoundEditor->setText (String());

    addAndMakeVisible (xMaxBoundEditor = new TextEditor ("x max bound editor"));
    xMaxBoundEditor->setMultiLine (false);
    xMaxBoundEditor->setReturnKeyStartsNewLine (false);
    xMaxBoundEditor->setReadOnly (false);
    xMaxBoundEditor->setScrollbarsShown (true);
    xMaxBoundEditor->setCaretVisible (true);
    xMaxBoundEditor->setPopupMenuEnabled (true);
    xMaxBoundEditor->setText (String());

    addAndMakeVisible (yMinBoundEditor = new TextEditor ("y min bound editor"));
    yMinBoundEditor->setMultiLine (false);
    yMinBoundEditor->setReturnKeyStartsNewLine (false);
    yMinBoundEditor->setReadOnly (false);
    yMinBoundEditor->setScrollbarsShown (true);
    yMinBoundEditor->setCaretVisible (true);
    yMinBoundEditor->setPopupMenuEnabled (true);
    yMinBoundEditor->setText (String());

    addAndMakeVisible (yMaxBoundEditor = new TextEditor ("y max bound editor"));
    yMaxBoundEditor->setMultiLine (false);
    yMaxBoundEditor->setReturnKeyStartsNewLine (false);
    yMaxBoundEditor->setReadOnly (false);
    yMaxBoundEditor->setScrollbarsShown (true);
    yMaxBoundEditor->setCaretVisible (true);
    yMaxBoundEditor->setPopupMenuEnabled (true);
    yMaxBoundEditor->setText (String());

    addAndMakeVisible (rotationBoundEditor = new TextEditor ("rotation bound editor"));
    rotationBoundEditor->setMultiLine (false);
    rotationBoundEditor->setReturnKeyStartsNewLine (false);
    rotationBoundEditor->setReadOnly (false);
    rotationBoundEditor->setScrollbarsShown (true);
    rotationBoundEditor->setCaretVisible (true);
    rotationBoundEditor->setPopupMenuEnabled (true);
    rotationBoundEditor->setText (String());


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

chuCalibrationComponent::~chuCalibrationComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    xBoundsSlider = nullptr;
    yBoundsSlider = nullptr;
    rotationSlider = nullptr;
    xBoundsGroup = nullptr;
    yBoundsGroup = nullptr;
    rotGroup = nullptr;
    xMinBoundEditor = nullptr;
    xMaxBoundEditor = nullptr;
    yMinBoundEditor = nullptr;
    yMaxBoundEditor = nullptr;
    rotationBoundEditor = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void chuCalibrationComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    g.setColour (Colours::grey);
    g.fillRect (12, 70, getWidth() - 50, getHeight() - 100);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void chuCalibrationComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    xBoundsSlider->setBounds (0, getHeight() - 30, getWidth() - 40, 30);
    yBoundsSlider->setBounds (getWidth() - 30, 70, 30, getHeight() - 110);
    rotationSlider->setBounds (getWidth() - 32, getHeight() - 32, 32, 32);
    xBoundsGroup->setBounds (6, 8, proportionOfWidth (0.3298f), 30 - -30);
    yBoundsGroup->setBounds (6 + proportionOfWidth (0.3298f), 8, proportionOfWidth (0.3298f), 30 - -30);
    rotGroup->setBounds ((6 + proportionOfWidth (0.3298f)) + proportionOfWidth (0.3298f), 8, proportionOfWidth (0.3298f), 30 - -30);
    xMinBoundEditor->setBounds (6 + roundFloatToInt (proportionOfWidth (0.3298f) * 0.0300f), 8 + 20, roundFloatToInt (proportionOfWidth (0.3298f) * 0.4500f), roundFloatToInt ((30 - -30) * 0.5000f));
    xMaxBoundEditor->setBounds (6 + roundFloatToInt (proportionOfWidth (0.3298f) * 0.9700f) - (roundFloatToInt (proportionOfWidth (0.3298f) * 0.4500f)), 8 + 20, roundFloatToInt (proportionOfWidth (0.3298f) * 0.4500f), roundFloatToInt ((30 - -30) * 0.5000f));
    yMinBoundEditor->setBounds ((6 + proportionOfWidth (0.3298f)) + roundFloatToInt (proportionOfWidth (0.3298f) * 0.0300f), 8 + 20, roundFloatToInt (proportionOfWidth (0.3298f) * 0.4500f), roundFloatToInt ((30 - -30) * 0.5000f));
    yMaxBoundEditor->setBounds ((6 + proportionOfWidth (0.3298f)) + roundFloatToInt (proportionOfWidth (0.3298f) * 0.9700f) - (roundFloatToInt (proportionOfWidth (0.3298f) * 0.4500f)), 8 + 20, roundFloatToInt (proportionOfWidth (0.3298f) * 0.4500f), roundFloatToInt ((30 - -30) * 0.5000f));
    rotationBoundEditor->setBounds (((6 + proportionOfWidth (0.3298f)) + proportionOfWidth (0.3298f)) + 10, 8 + 20, proportionOfWidth (0.3298f) - 20, roundFloatToInt ((30 - -30) * 0.5000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void chuCalibrationComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == xBoundsSlider)
    {
        //[UserSliderCode_xBoundsSlider] -- add your slider handling code here..
        //[/UserSliderCode_xBoundsSlider]
    }
    else if (sliderThatWasMoved == yBoundsSlider)
    {
        //[UserSliderCode_yBoundsSlider] -- add your slider handling code here..
        //[/UserSliderCode_yBoundsSlider]
    }
    else if (sliderThatWasMoved == rotationSlider)
    {
        //[UserSliderCode_rotationSlider] -- add your slider handling code here..
        //[/UserSliderCode_rotationSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void chuCalibrationComponent::showCalibrationDialog() {
    DialogWindow::LaunchOptions dlo;
    dlo.dialogTitle = "Laser calibration window";
    dlo.escapeKeyTriggersCloseButton = true;
    dlo.useNativeTitleBar = true;
    dlo.resizable = true;
    chuCalibrationComponent* chuCalib = new chuCalibrationComponent();
    dlo.content = *new OptionalScopedPointer<Component>(chuCalib, true);
    dlo.launchAsync();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="chuCalibrationComponent"
                 componentName="" parentClasses="public Component" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="600">
  <BACKGROUND backgroundColour="ff000000">
    <RECT pos="12 70 50M 100M" fill="solid: ff808080" hasStroke="0"/>
  </BACKGROUND>
  <SLIDER name="x bounds slider" id="9c1a14f81290c611" memberName="xBoundsSlider"
          virtualName="" explicitFocusOrder="0" pos="0 30R 40M 30" bkgcol="0"
          min="0" max="100" int="0" style="TwoValueHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="y bounds slider" id="24684aa4d940a864" memberName="yBoundsSlider"
          virtualName="" explicitFocusOrder="0" pos="30R 70 30 110M" min="0"
          max="10" int="0" style="TwoValueVertical" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="rotation slider" id="7c8d859aaaa0af33" memberName="rotationSlider"
          virtualName="" explicitFocusOrder="0" pos="32R 32R 32 32" trackcol="ffffffff"
          rotarysliderfill="fffffefe" rotaryslideroutline="ffffffff" min="0"
          max="10" int="0" style="Rotary" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <GROUPCOMPONENT name="x bounds group" id="ea8702e7b5f625ac" memberName="xBoundsGroup"
                  virtualName="" explicitFocusOrder="0" pos="6 8 33.024% -30M"
                  posRelativeH="9c1a14f81290c611" outlinecol="66ffffff" textcol="ffffffff"
                  title="X bounds" textpos="33"/>
  <GROUPCOMPONENT name="y bounds group" id="f4b77cb6090cc4e4" memberName="yBoundsGroup"
                  virtualName="" explicitFocusOrder="0" pos="0R 8 33.024% -30M"
                  posRelativeX="ea8702e7b5f625ac" posRelativeH="9c1a14f81290c611"
                  outlinecol="66ffffff" textcol="ffffffff" title="Y bounds" textpos="33"/>
  <GROUPCOMPONENT name="rotation group" id="cad08fc782f89d49" memberName="rotGroup"
                  virtualName="" explicitFocusOrder="0" pos="0R 8 33.024% -30M"
                  posRelativeX="f4b77cb6090cc4e4" posRelativeH="9c1a14f81290c611"
                  outlinecol="66ffffff" textcol="ffffffff" title="Rotation" textpos="33"/>
  <TEXTEDITOR name="x min bound editor" id="8692178c70b7772a" memberName="xMinBoundEditor"
              virtualName="" explicitFocusOrder="0" pos="2.811% 20 44.98% 50%"
              posRelativeX="ea8702e7b5f625ac" posRelativeY="ea8702e7b5f625ac"
              posRelativeW="ea8702e7b5f625ac" posRelativeH="ea8702e7b5f625ac"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="x max bound editor" id="d0c3041725b3d7d2" memberName="xMaxBoundEditor"
              virtualName="" explicitFocusOrder="0" pos="97.189%r 20 44.98% 50%"
              posRelativeX="ea8702e7b5f625ac" posRelativeY="ea8702e7b5f625ac"
              posRelativeW="ea8702e7b5f625ac" posRelativeH="ea8702e7b5f625ac"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="y min bound editor" id="4a26618a46c6b857" memberName="yMinBoundEditor"
              virtualName="" explicitFocusOrder="0" pos="2.811% 20 44.98% 50%"
              posRelativeX="f4b77cb6090cc4e4" posRelativeY="f4b77cb6090cc4e4"
              posRelativeW="f4b77cb6090cc4e4" posRelativeH="f4b77cb6090cc4e4"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="y max bound editor" id="81ac6adac23e4f93" memberName="yMaxBoundEditor"
              virtualName="" explicitFocusOrder="0" pos="97.189%r 20 44.98% 50%"
              posRelativeX="f4b77cb6090cc4e4" posRelativeY="f4b77cb6090cc4e4"
              posRelativeW="f4b77cb6090cc4e4" posRelativeH="f4b77cb6090cc4e4"
              initialText="" multiline="0" retKeyStartsLine="0" readonly="0"
              scrollbars="1" caret="1" popupmenu="1"/>
  <TEXTEDITOR name="rotation bound editor" id="6eb5c01cc8fb27c7" memberName="rotationBoundEditor"
              virtualName="" explicitFocusOrder="0" pos="10 20 20M 50%" posRelativeX="cad08fc782f89d49"
              posRelativeY="f4b77cb6090cc4e4" posRelativeW="cad08fc782f89d49"
              posRelativeH="f4b77cb6090cc4e4" initialText="" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="1" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
