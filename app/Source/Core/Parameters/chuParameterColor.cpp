/*
  ==============================================================================

    chuParameterColor.cpp
    Created: 16 Jan 2016 11:30:50pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterColor.h"

chuParameterColor::chuParameterColor(const String& _name, const Color& _color, const chuParameterOptions& _options)
: chuParameter(_name, _options)
{
    setValue(_color);
}

void chuParameterColor::oscMessageReceived(const OSCMessage& message)
{
}

class chuParameterColorButton : public PropertyComponent, public Button::Listener, public ChangeListener
{
public:
    chuParameterColorButton(chuParameterColor* pParam)
    : PropertyComponent(pParam->getName()), param(pParam)
    {
        button.setTriggeredOnMouseDown(true);
        button.addListener(this);
        button.setColour(TextButton::buttonColourId, param->getValue());
        addAndMakeVisible(button);
    }

    virtual void buttonClicked(Button* b) override
    {
        if (b != &button) {
            return;
        }

        ColourSelector* colorSelector = new ColourSelector();
        colorSelector->setName(param->getName());
        colorSelector->setCurrentColour(param->getValue());
        colorSelector->addChangeListener(this);
        colorSelector->setColour(ColourSelector::backgroundColourId, Colors::transparentBlack);
        colorSelector->setSize(300, 400);

        CallOutBox::launchAsynchronously(colorSelector, getScreenBounds(), nullptr);
    }

    virtual void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (ColourSelector* cs = dynamic_cast<ColourSelector*> (source))
        {
            param->setValue(cs->getCurrentColour());
            button.setColour(TextButton::buttonColourId, param->getValue());
        }
    }

    virtual void refresh() override
    {

    }

private:
    TextButton button;
    chuParameterColor* param;
};

PropertyComponent* chuParameterColor::createComponent()
{
    return new chuParameterColorButton(this);
}
