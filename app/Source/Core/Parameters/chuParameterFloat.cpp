/*
  ==============================================================================

    chuParameterFloat.cpp
    Created: 16 Jan 2016 11:30:13pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterFloat.h"

chuParameterFloat::chuParameterFloat(const String& _name, float _min, float _max, float _defaultValue,
                                     const chuParameterOptions& _options)
: chuParameter(_name, _options), minValue(_min), maxValue(_max), value(_defaultValue)
{
}

void chuParameterFloat::oscMessageReceived(const OSCMessage& message)
{
    OSCArgument* arg = message.begin();
    if (arg && arg->isFloat32())
    {
        value = arg->getFloat32();
    }
    else if (arg && arg->isInt32())
    {
        value = (float)arg->getInt32();
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
