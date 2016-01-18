/*
  ==============================================================================

    chuParameterInt.cpp
    Created: 16 Jan 2016 11:30:19pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterInt.h"

chuParameterInt::chuParameterInt(const String& _name, int _min, int _max, int _defaultValue,
                                 const chuParameterOptions& _options)
: chuParameter(_name, _options), minValue(_min), maxValue(_max), value(_defaultValue)
{
}

void chuParameterInt::oscMessageReceived(const OSCMessage& message)
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

