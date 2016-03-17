/*
  ==============================================================================

    chuParameterInt.cpp
    Created: 16 Jan 2016 11:30:19pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterInt.h"

chuParameterInt::chuParameterInt(const String& name, int min, int max, int defaultValue,
                                 const chuParameterOptions& options)
: chuParameter(name, options)
{
    data.setProperty("_type", "int", nullptr);
    setMinValue(min);
    setMaxValue(max);
    setValue(defaultValue);
}

int chuParameterInt::getMinValue() const
{
    return data.getProperty("min");
}

int chuParameterInt::getMaxValue() const
{
    return data.getProperty("max");
}

int chuParameterInt::getValue() const
{
    return data.getProperty("value");
}

void chuParameterInt::setMinValue(int newMin)
{
    data.setProperty("min", newMin, nullptr);
}

void chuParameterInt::setMaxValue(int newMax)
{
    data.setProperty("max", newMax, nullptr);
}

void chuParameterInt::setValue(int newValue)
{
    if (newValue < getMinValue())
    {
        newValue = getMinValue();
    }
    else if (newValue > getMaxValue())
    {
        newValue = getMaxValue();
    }

    data.setProperty("value", newValue, nullptr);
}

void chuParameterInt::deserialize(ValueTree saved)
{
    if (saved.hasProperty("_type") &&
        saved.getProperty("_type") == "int" &&
        saved.hasProperty("value"))
    {
        int savedValue = saved.getProperty("value");
        data.setProperty("value", savedValue, nullptr);
    }
}

void chuParameterInt::oscMessageReceived(const OSCMessage& message)
{
    OSCArgument* arg = message.begin();
    if (arg && arg->isInt32())
    {
        setValue(arg->getInt32());
    }
    else if (arg && arg->isFloat32())
    {
        setValue(floor(arg->getFloat32()));
    }
}

class chuParameterIntSlider : public SliderPropertyComponent
{
public:
    chuParameterIntSlider(chuParameterInt* pParam)
    : SliderPropertyComponent(pParam->getName(), pParam->getMinValue(), pParam->getMaxValue(), 1.0)
    , param(pParam)
    {
        slider.setSliderStyle(Slider::LinearBar);
        slider.setValue(param->getValue());
    }
    virtual double getValue() const override
    {
        return param->getValue();
    }
    virtual void setValue(double newValue) override
    {
        param->setValue((int)newValue);
    }

private:
    chuParameterInt* param;
};

PropertyComponent* chuParameterInt::createComponent()
{
    return new chuParameterIntSlider(this);
}

