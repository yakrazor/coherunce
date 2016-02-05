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

#ifndef __JUCE_HEADER_1374590B8F463A1C__
#define __JUCE_HEADER_1374590B8F463A1C__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "chuParameterString.h"
#include "chuGeneratorPreview.h"
#include "chuGenJavascript.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class chuCodeEditor  : public Component,
                       private Timer,
                       private CodeDocument::Listener
{
public:
    //==============================================================================
    chuCodeEditor (chuParameterString* param);
    ~chuCodeEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void codeDocumentTextInserted(const String&, int) override;
    void codeDocumentTextDeleted(int, int) override;
    void timerCallback() override;
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    CodeDocument document;
    chuParameterString* param;
    ScopedPointer<chuGenJavascript> jsGen;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<CodeEditorComponent> codeEditor;
    ScopedPointer<chuGeneratorPreview> preview;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (chuCodeEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_1374590B8F463A1C__
