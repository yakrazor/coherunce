/*
  ==============================================================================

    chuParameterBool.cpp
    Created: 16 Jan 2016 11:30:36pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterBool.h"

chuParameterBool::chuParameterBool(const String& _name, bool _defaultValue, const chuParameterOptions& _options)
: chuParameter(_name, _options), value(_defaultValue)
{
}

void chuParameterBool::oscMessageReceived(const OSCMessage& message)
{
    OSCArgument* arg = message.begin();
    if (arg && arg->isInt32())
    {
        value = (float)arg->getInt32();
    }
    else if (arg && arg->isFloat32())
    {
        value = (int)arg->getFloat32();
    }
}

class chuParameterBoolButton : public PropertyComponent, public Button::Listener
{
public:
    chuParameterBoolButton(chuParameterBool* pParam)
    : PropertyComponent(pParam->getName()), param(pParam)
    {
        addAndMakeVisible(button);
        button.setTriggeredOnMouseDown(true);
        button.addListener(this);
        refresh();
    }
    virtual void buttonClicked(Button* button) override
    {
        param->setValue(!param->getValue());
        refresh();
    }

    virtual void refresh() override
    {
        button.setToggleState(param->getValue(), dontSendNotification);
        button.setButtonText(param->getValue() ? "ON" : "off");
    }

private:
    TextButton button;
    chuParameterBool* param;
};

PropertyComponent* chuParameterBool::createComponent()
{
    return new chuParameterBoolButton(this);
}
