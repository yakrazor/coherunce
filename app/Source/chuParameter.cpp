/*
  ==============================================================================

    chuParameter.cpp
    Created: 2 Jan 2016 11:47:13am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameter.h"

chuParameterOptions chuParameterOptions::Default;


chuParameter::chuParameter(String _name, const chuParameterOptions& _options)
: name(_name), options(_options)
{

}


class chuParameterFloatSlider : public Slider
{
public:
    chuParameterFloatSlider(chuParameterFloat* pParam) : param(pParam)
    {
        setSliderStyle(Slider::LinearBar);
        setRange(param->minValue, param->maxValue);
        setValue(param->value);
    }
    virtual void valueChanged() override
    {
        param->value = (float)getValue();
    }

private:
    chuParameterFloat* param;
};

chuParameterFloat::chuParameterFloat(String _name, float _min, float _max, float _defaultValue,
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

Component* chuParameterFloat::createComponent()
{
    return new chuParameterFloatSlider(this);
}