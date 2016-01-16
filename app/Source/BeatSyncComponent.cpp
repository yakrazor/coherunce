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
    tapTempoButton->setButtonText (TRANS("TAP"));
    tapTempoButton->addListener (this);

    addAndMakeVisible (syncButton = new TextButton ("syncButton"));
    syncButton->setButtonText (TRANS("Sync"));
    syncButton->addListener (this);

    addAndMakeVisible (bpmLabel = new Label ("bpmLabel",
                                             TRANS("120.00")));
    bpmLabel->setFont (Font (Font::getDefaultMonospacedFontName(), 54.10f, Font::plain));
    bpmLabel->setJustificationType (Justification::centred);
    bpmLabel->setEditable (false, false, false);
    bpmLabel->setColour (TextEditor::textColourId, Colours::black);
    bpmLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (300, 100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

BeatSyncComponent::~BeatSyncComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tapTempoButton = nullptr;
    syncButton = nullptr;
    bpmLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
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

    tapTempoButton->setBounds (8, 64, 80, 24);
    syncButton->setBounds (165, 64, 80, 24);
    bpmLabel->setBounds (8, 8, 300, 48);
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
        //[/UserButtonCode_tapTempoButton]
    }
    else if (buttonThatWasClicked == syncButton)
    {
        //[UserButtonCode_syncButton] -- add your button handler code here..
        getApp()->getFrameTimer()->syncBeatClock();
        //[/UserButtonCode_syncButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
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
                 fixedSize="1" initialWidth="300" initialHeight="100">
  <BACKGROUND backgroundColour="ffffffff"/>
  <TEXTBUTTON name="tapTempoButton" id="21c8149665c84b17" memberName="tapTempoButton"
              virtualName="" explicitFocusOrder="0" pos="8 64 96 32" buttonText="TAP"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="syncButton" id="da0a5bdc38102823" memberName="syncButton"
              virtualName="" explicitFocusOrder="0" pos="200 64 95 32" buttonText="Sync"
              connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="bpmLabel" id="4b142ec3d9feefb7" memberName="bpmLabel" virtualName=""
         explicitFocusOrder="0" pos="8 8 280 48" edTextCol="ff000000"
         edBkgCol="0" labelText="120.00" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default monospaced font" fontsize="54.100000000000001421"
         bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
