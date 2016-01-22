/*
  ==============================================================================

    chuParameterString.cpp
    Created: 16 Jan 2016 11:30:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterString.h"
#include "chuApplication.h"

chuParameterString::chuParameterString(const String& _name, const String& _str, const chuParameterOptions& _options)
: chuParameter(_name, _options)
{
    setValue(_str);
}

class CodeEditorWindow : public DocumentWindow, private Timer, private CodeDocument::Listener
{
public:
    CodeEditorWindow(const String& name, chuParameterString* param)
    : DocumentWindow(name, Colours::black, allButtons), param(param)
    {
        setUsingNativeTitleBar(true);
        document.addListener(this);
        setResizable(true, true);

        editor = new CodeEditorComponent(document, nullptr);
        editor->loadContent(param->getValue());
        setContentOwned(editor, false);

        addKeyListener(getApp()->getApplicationCommandManager().getKeyMappings());
    }

    ~CodeEditorWindow()
    {
    }

    virtual void closeButtonPressed() override
    {
        delete this;
    }

private:
    CodeDocument document;
    ScopedPointer<CodeEditorComponent> editor;
    chuParameterString* param;

    void codeDocumentTextInserted(const String&, int) override
    {
        startTimer(300);
    }

    void codeDocumentTextDeleted(int, int) override
    {
        startTimer(300);
    }

    void timerCallback() override
    {
        stopTimer();
        if (param)
        {
            param->setValue(document.getAllContent());
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CodeEditorWindow)
};

class chuParameterTextEditor : public PropertyComponent, public Button::Listener
{
public:
    chuParameterTextEditor(chuParameterString* pParam)
    : PropertyComponent(pParam->getName()), param(pParam)
    {
        button.setButtonText("Edit...");
        button.setTriggeredOnMouseDown(true);
        button.addListener(this);
        addAndMakeVisible(button);
    }

    virtual void buttonClicked(Button* b) override
    {
        if (b != &button) {
            return;
        }

        if (!window) {
            window = new CodeEditorWindow(param->getName(), param);
            auto buttonBounds = b->getScreenBounds();
            int codeWindowWidth = 550;
            int codeWindowHeight = 400;
            window->setBounds(buttonBounds.getCentreX() - codeWindowWidth,
                              buttonBounds.getCentreY() + 30,
                              codeWindowWidth,
                              codeWindowHeight);
        }
        window->setVisible(true);
    }

    virtual void refresh() override
    {
    }

private:
    TextButton button;
    Component::SafePointer<CodeEditorWindow> window;

    chuParameterString* param;
};

void chuParameterString::oscMessageReceived(const OSCMessage& message)
{
}

PropertyComponent* chuParameterString::createComponent()
{
    return new chuParameterTextEditor(this);
}