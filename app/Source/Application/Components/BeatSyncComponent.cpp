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
#include "chuApplication.h"
//[/Headers]

#include "BeatSyncComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BeatSyncComponent::BeatSyncComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (tapTempoButton = new TextButton ("tapTempoButton"));
    tapTempoButton->setTooltip (TRANS("Tap here to calculate the BPM"));
    tapTempoButton->setButtonText (TRANS("TAP"));
    tapTempoButton->addListener (this);

    addAndMakeVisible (syncButton = new TextButton ("syncButton"));
    syncButton->setTooltip (TRANS("Triggers a downbeat"));
    syncButton->setButtonText (TRANS("Sync"));
    syncButton->addListener (this);

    addAndMakeVisible (bpmLabel = new Label ("bpmLabel",
                                             TRANS("120.00")));
    bpmLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 54.10f, Font::plain));
    bpmLabel->setJustificationType (Justification::centredLeft);
    bpmLabel->setEditable (false, false, false);
    bpmLabel->setColour (Label::backgroundColourId, Colour (0x00000000));
    bpmLabel->setColour (Label::textColourId, Colours::white);
    bpmLabel->setColour (TextEditor::textColourId, Colours::black);
    bpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (stopStartButton = new TextButton ("new button"));
    stopStartButton->setTooltip (TRANS("Toggles between running and stopped clock"));
    stopStartButton->setButtonText (TRANS("Running"));
    stopStartButton->addListener (this);

    addAndMakeVisible (externalInternalToggle = new TextButton ("new button"));
    externalInternalToggle->setTooltip (TRANS("Toggles between internal and external clock"));
    externalInternalToggle->setButtonText (TRANS("External"));
    externalInternalToggle->addListener (this);

    addAndMakeVisible (bpmSlider = new Slider ("new slider"));
    bpmSlider->setTooltip (TRANS("Drag this to manually set the BPM"));
    bpmSlider->setRange (60, 200, 0);
    bpmSlider->setSliderStyle (Slider::LinearHorizontal);
    bpmSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    bpmSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (250, 100);


    //[Constructor] You can add your own custom stuff here..
    bpmListen = new bpmListener(this);
    clockSrcListen = new clockSourceListener(this);
    runningListen = new runningListener(this);
    getApp()->getFrameTimer()->bpm->addListener(bpmListen);
    getApp()->getFrameTimer()->external->addListener(clockSrcListen);
    getApp()->getFrameTimer()->running->addListener(runningListen);
    //[/Constructor]
}

BeatSyncComponent::~BeatSyncComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tapTempoButton = nullptr;
    syncButton = nullptr;
    bpmLabel = nullptr;
    stopStartButton = nullptr;
    externalInternalToggle = nullptr;
    bpmSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    getApp()->getFrameTimer()->bpm->removeListener(bpmListen);
    //[/Destructor]
}

//==============================================================================
void BeatSyncComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BeatSyncComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    tapTempoButton->setBounds (8, 72, 40, 24);
    syncButton->setBounds (48, 72, 48, 24);
    bpmLabel->setBounds (0, 0, 184, 48);
    stopStartButton->setBounds (96, 72, 64, 24);
    externalInternalToggle->setBounds (160, 72, 80, 24);
    bpmSlider->setBounds (8, 48, 232, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void BeatSyncComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == tapTempoButton)
    {
        //[UserButtonCode_tapTempoButton] -- add your button handler code here..
        getApp()->getFrameTimer()->tapTempo();
        //[/UserButtonCode_tapTempoButton]
    }
    else if (buttonThatWasClicked == syncButton)
    {
        //[UserButtonCode_syncButton] -- add your button handler code here..
        getApp()->getFrameTimer()->syncBeatClock();
        //[/UserButtonCode_syncButton]
    }
    else if (buttonThatWasClicked == stopStartButton)
    {
        //[UserButtonCode_stopStartButton] -- add your button handler code here..
        getApp()->getFrameTimer()->setRunning(!getApp()->getFrameTimer()->isClockRunning());
        //[/UserButtonCode_stopStartButton]
    }
    else if (buttonThatWasClicked == externalInternalToggle)
    {
        //[UserButtonCode_externalInternalToggle] -- add your button handler code here..
        getApp()->getFrameTimer()->setExternalClock(!getApp()->getFrameTimer()->isClockExternal());
        //[/UserButtonCode_externalInternalToggle]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void BeatSyncComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == bpmSlider)
    {
        //[UserSliderCode_bpmSlider] -- add your slider handling code here..
        getApp()->getFrameTimer()->setBpm(bpmSlider->getValue());
        //[/UserSliderCode_bpmSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void BeatSyncComponent::bpmListener::valueChanged(Value& value) {
    double bpm = value.getValue();
    beatSyncComponent->bpmLabel->setText(String::formatted("%.2f", bpm), NotificationType::dontSendNotification);
    beatSyncComponent->bpmSlider->setValue(bpm);
}

void BeatSyncComponent::clockSourceListener::valueChanged(Value& value) {
    bool isExternal = value.getValue();
    if(isExternal) {
        beatSyncComponent->externalInternalToggle->setButtonText("External");
    } else {
        beatSyncComponent->externalInternalToggle->setButtonText("Internal");
    }
}

void BeatSyncComponent::runningListener::valueChanged(Value& value) {
    bool isRunning = value.getValue();
    if(isRunning) {
        beatSyncComponent->stopStartButton->setButtonText("Running");
    } else {
        beatSyncComponent->stopStartButton->setButtonText("Stopped");
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BeatSyncComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="250" initialHeight="100">
  <BACKGROUND backgroundColour="ff000000"/>
  <TEXTBUTTON name="tapTempoButton" id="21c8149665c84b17" memberName="tapTempoButton"
              virtualName="" explicitFocusOrder="0" pos="8 72 40 24" tooltip="Tap here to calculate the BPM"
              buttonText="TAP" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="syncButton" id="da0a5bdc38102823" memberName="syncButton"
              virtualName="" explicitFocusOrder="0" pos="48 72 48 24" tooltip="Triggers a downbeat"
              buttonText="Sync" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="bpmLabel" id="4b142ec3d9feefb7" memberName="bpmLabel" virtualName=""
         explicitFocusOrder="0" pos="0 0 184 48" bkgCol="0" textCol="ffffffff"
         edTextCol="ff000000" edBkgCol="0" labelText="120.00" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default monospaced font"
         fontsize="54.100000000000001421" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="new button" id="d9f2aa84eb93e4c2" memberName="stopStartButton"
              virtualName="" explicitFocusOrder="0" pos="96 72 64 24" tooltip="Toggles between running and stopped clock"
              buttonText="Running" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new button" id="62d76ba966716f06" memberName="externalInternalToggle"
              virtualName="" explicitFocusOrder="0" pos="160 72 80 24" tooltip="Toggles between internal and external clock"
              buttonText="External" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="new slider" id="307736032e15edaa" memberName="bpmSlider"
          virtualName="" explicitFocusOrder="0" pos="8 48 232 24" tooltip="Drag this to manually set the BPM"
          min="60" max="200" int="0" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
