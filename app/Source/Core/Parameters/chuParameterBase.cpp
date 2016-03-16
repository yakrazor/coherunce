/*
  ==============================================================================

    chuParameterBase.cpp
    Created: 2 Jan 2016 11:47:13am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterBase.h"
#include "chuApplication.h"

chuParameterOptions chuParameterOptions::Default;

chuParameter::chuParameter(const String& name, const chuParameterOptions& paramOptions)
: options(paramOptions)
{
    data = ValueTree("parameter");
    data.setProperty("name", name, nullptr);
}

chuParameterProvider::chuParameterProvider(const String& name, ValueTree source)
{
    data = source;
    if (!data.hasProperty("name")) {
        data.setProperty("name", name, nullptr);
    }
}

String chuParameterProvider::getName()
{
    if (data.isValid())
    {
        return data.getProperty("name");
    } else {
        return "";
    }
}

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



