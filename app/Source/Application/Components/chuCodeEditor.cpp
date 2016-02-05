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

#include "chuCodeEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
chuCodeEditor::chuCodeEditor (chuParameterString* param)
    : param(param)
{
    //[Constructor_pre] You can add your own custom stuff here..
    document.addListener(this);
    jsGen = new chuGenJavascript();
    jsGen->code->setValue(param->getValue());

    //[/Constructor_pre]

    addAndMakeVisible (codeEditor = new CodeEditorComponent (document, nullptr));
    codeEditor->setName ("CODE_EDITOR");

    addAndMakeVisible (preview = new chuGeneratorPreview(jsGen));
    preview->setName ("CODE_PREVIEW");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    codeEditor->loadContent(param->getValue());
    preview->startPreviewUpdate();
    //[/Constructor]
}

chuCodeEditor::~chuCodeEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    codeEditor = nullptr;
    preview = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void chuCodeEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void chuCodeEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    codeEditor->setBounds (0, 0, proportionOfWidth (0.5000f), proportionOfHeight (1.0000f));
    preview->setBounds (proportionOfWidth (0.5000f), 0, proportionOfWidth (0.5000f), proportionOfHeight (1.0000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void chuCodeEditor::codeDocumentTextInserted(const String&, int)
{
    startTimer(300);
}

void chuCodeEditor::codeDocumentTextDeleted(int, int)
{
    startTimer(300);
}

void chuCodeEditor::timerCallback()
{
    stopTimer();
    if (param)
    {
        param->setValue(document.getAllContent());
        jsGen->code->setValue(param->getValue());
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="chuCodeEditor" componentName=""
                 parentClasses="public Component, private Timer, private CodeDocument::Listener"
                 constructorParams="chuParameterString* param" variableInitialisers="param(param) "
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff000000"/>
  <GENERICCOMPONENT name="CODE_EDITOR" id="a324a8a3f1c9f9fa" memberName="codeEditor"
                    virtualName="" explicitFocusOrder="0" pos="0 0 50% 100%" class="CodeEditorComponent"
                    params="document, nullptr"/>
  <GENERICCOMPONENT name="CODE_PREVIEW" id="95eb97ad47d1b30b" memberName="preview"
                    virtualName="" explicitFocusOrder="0" pos="50% 0 50% 100%" class="chuGeneratorPreview"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
