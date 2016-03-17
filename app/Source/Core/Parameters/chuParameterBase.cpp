/*
  ==============================================================================

    chuParameterBase.cpp
    Created: 2 Jan 2016 11:47:13am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuParameterBase.h"
#include "chuApplication.h"
#include "chuOSCManager.h"

chuParameterOptions chuParameterOptions::Default;

#include <map>
#include <utility>

std::map<String, int> numberingMap;

String getNumberedName(String base)
{
    auto iter = numberingMap.find(base);
    if (iter == numberingMap.end())
    {
        iter = numberingMap.insert(std::make_pair(base, 1)).first;
    }
    return base + String(iter->second++);
}

chuParameter::chuParameter(const String& name, const chuParameterOptions& paramOptions)
: options(paramOptions)
{
    data = ValueTree("parameter");
    data.setProperty("name", name, nullptr);
}

chuParameterProvider::chuParameterProvider(const String& typeName, ValueTree source)
{
    data = source;
    data.setProperty("_type", typeName, nullptr);
    if (!data.hasProperty("name"))
    {
        data.setProperty("name", getNumberedName(typeName), nullptr);
    }
}

void chuParameterProvider::getParamList(std::vector<chuParameter*>& params) const
{
    for (auto iter = parameters.begin(); iter != parameters.end(); iter++)
    {
        params.push_back(*iter);
    }
}

const String chuParameterProvider::getType() const
{
    if (data.isValid())
    {
        return data.getProperty("_type");
    } else {
        return "";
    }
}

const String chuParameterProvider::getName() const
{
    if (data.isValid())
    {
        return data.getProperty("name");
    } else {
        return "";
    }
}

void chuParameterProvider::setName(String name)
{
    if (data.isValid())
    {
        data.setProperty("name", name, nullptr);
    }
}

void chuParameterProvider::addParameter(chuParameter* newParam)
{
    parameters.add(newParam);
    auto saved = data.getChildWithProperty("name", newParam->getName());
    if (saved.isValid())
    {
        newParam->deserialize(saved);
        data.removeChild(saved, nullptr);
    }
    data.addChild(newParam->data, data.getNumChildren(), nullptr);

    if (getOSCRoot().isNotEmpty())
    {
        newParam->listenAtOSCAddress(getOSCRoot());
    }
}

void chuParameter::listenAtOSCAddress(const String& prefix)
{
    chuOSCManager::getReceiver()->removeListener(this);
    String fullAddress = prefix + "/param/" + getName();
    fullAddress = fullAddress.replaceCharacters(" #*,?[]{}", "_");
    printf("[OSC] Registering OSC address %s\n", fullAddress.toRawUTF8());
    chuOSCManager::getReceiver()->addListener(this, fullAddress);
}

PropertyPanel* chuParameterProvider::createPanel() const
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

    String displayName = getName();
    String type = getType();
    if (!displayName.contains(type))
    {
        displayName += " (" + type + ")";
    }

    auto panel = new PropertyPanel();
    panel->addSection(displayName + " Parameters", propertyComponents);
    return panel;
}



