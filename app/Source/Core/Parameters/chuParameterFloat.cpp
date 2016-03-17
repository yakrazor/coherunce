/*
  ==============================================================================

    chuParameterFloat.cpp
    Created: 16 Jan 2016 11:30:13pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterFloat.h"

chuParameterFloat::chuParameterFloat(const String& name, float min, float max, float defaultValue,
                                     const chuParameterOptions& options)
: chuParameter(name, options)
{
    data.setProperty("_type", "float", nullptr);
    setMinValue(min);
    setMaxValue(max);
    setValue(defaultValue);
}

float chuParameterFloat::getMinValue() const
{
    return data.getProperty("min");
}

float chuParameterFloat::getMaxValue() const
{
    return data.getProperty("max");
}

float chuParameterFloat::getValue() const
{
    return data.getProperty("value");
}

void chuParameterFloat::setMinValue(float newMin)
{
    data.setProperty("min", newMin, nullptr);
}

void chuParameterFloat::setMaxValue(float newMax)
{
    data.setProperty("max", newMax, nullptr);
}

void chuParameterFloat::setValue(float newValue)
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

void chuParameterFloat::deserialize(ValueTree saved)
{
    if (saved.hasProperty("_type") &&
        saved.getProperty("_type") == "float" &&
        saved.hasProperty("value"))
    {
        float savedValue = saved.getProperty("value");
        data.setProperty("value", savedValue, nullptr);
    }
}

void chuParameterFloat::oscMessageReceived(const OSCMessage& message)
{
    OSCArgument* arg = message.begin();
    if (arg && arg->isFloat32())
    {
        setValue(arg->getFloat32());
    }
    else if (arg && arg->isInt32())
    {
        setValue((float)arg->getInt32());
    }
}


class chuParameterFloatSlider : public SliderPropertyComponent
{
public:
    chuParameterFloatSlider(chuParameterFloat* pParam)
    : SliderPropertyComponent(pParam->getName(), pParam->getMinValue(), pParam->getMaxValue(), 0)
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
        param->setValue((float)newValue);
    }

private:
    chuParameterFloat* param;
};

PropertyComponent* chuParameterFloat::createComponent()
{
    return new chuParameterFloatSlider(this);
}
