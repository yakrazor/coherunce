/*
  ==============================================================================

    chuParameterBool.cpp
    Created: 16 Jan 2016 11:30:36pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterBool.h"

chuParameterBool::chuParameterBool(const String& name, bool defaultValue, const chuParameterOptions& options)
: chuParameter(name, options)
{
    data.setProperty("_type", "bool", nullptr);
    setValue(defaultValue);
}

bool chuParameterBool::getValue() const
{
    return data.getProperty("value");
}

void chuParameterBool::setValue(bool newValue)
{
    data.setProperty("value", newValue, nullptr);
}

void chuParameterBool::deserialize(ValueTree saved)
{
    if (saved.hasProperty("_type") &&
        saved.getProperty("_type") == "bool" &&
        saved.hasProperty("value"))
    {
        bool savedValue = saved.getProperty("value");
        setValue(savedValue);
    }
}

void chuParameterBool::oscMessageReceived(const OSCMessage& message)
{
    OSCArgument* arg = message.begin();
    if (arg && arg->isInt32())
    {
        setValue(arg->getInt32() != 0);
    }
    else if (arg && arg->isFloat32())
    {
        setValue(arg->getFloat32() != 0);
    }
    else if (arg && arg->isString())
    {
        setValue(arg->getString().toLowerCase() == "true");
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
