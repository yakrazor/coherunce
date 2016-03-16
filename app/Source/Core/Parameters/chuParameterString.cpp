/*
  ==============================================================================

    chuParameterString.cpp
    Created: 16 Jan 2016 11:30:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterString.h"
#include "chuApplication.h"
#include "chuCodeEditor.h"

chuParameterString::chuParameterString(const String& name, const String& str, const chuParameterOptions& options)
: chuParameter(name, options)
{
    data.setProperty("_type", "string", nullptr);
    setValue(str);
}

const String chuParameterString::getValue() const
{
    return data.getProperty("value");
}

void chuParameterString::setValue(const String& str)
{
    data.setProperty("value", str, nullptr);
}

void chuParameterString::deserialize(ValueTree saved)
{
    if (saved.hasProperty("_type") &&
        saved.getProperty("_type") == "string" &&
        saved.hasProperty("value"))
    {
        setValue(saved.getProperty("value"));
    }
}

class CodeEditorWindow : public DocumentWindow
{
public:
    CodeEditorWindow(const String& name, chuParameterString* param)
    : DocumentWindow(name, Colours::black, allButtons)
    {
        setUsingNativeTitleBar(true);
        setResizable(true, true);

        editor = new chuCodeEditor(param);
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
    ScopedPointer<chuCodeEditor> editor;

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
            int codeWindowWidth = 1100;
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