/*
  ==============================================================================

    chuParameter.cpp
    Created: 2 Jan 2016 11:47:13am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameter.h"

chuParameterOptions chuParameterOptions::Default;


PropertyPanel* chuParameterProvider::createPanel()
{
    Array<PropertyComponent*> propertyComponents;
    std::vector<chuParameter*> params;

    getParamList(params);
    for (auto& param : params)
    {
        if (!param->getOptions().isUserVisible)
            continue;
        auto pc = param->createComponent();
        pc->setColour(PropertyComponent::backgroundColourId, Colours::transparentBlack);
        propertyComponents.add(pc);
    }

    auto panel = new PropertyPanel();
    panel->addSection(getName() + " Parameters", propertyComponents);
    return panel;
}



chuParameter::chuParameter(const String& _name, const chuParameterOptions& _options)
: name(_name), options(_options)
{

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

PropertyComponent* chuParameterFloat::createComponent()
{
    return new chuParameterFloatSlider(this);
}

// -------------------------------------

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

PropertyComponent* chuParameterInt::createComponent()
{
    return new chuParameterIntSlider(this);
}


// -------------------------------------


chuParameterColor::chuParameterColor(const String& _name, const Color& _color, const chuParameterOptions& _options)
: chuParameter(_name, _options)
{
    setValue(_color);
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

    virtual void refresh()
    {
        
    }

private:
    TextButton button;
    chuParameterColor* param;
};


void chuParameterColor::oscMessageReceived(const OSCMessage& message)
{
}

PropertyComponent* chuParameterColor::createComponent()
{
    return new chuParameterColorButton(this);
}